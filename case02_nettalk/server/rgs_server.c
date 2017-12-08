#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>
#include <sqlite3.h>
#include <unistd.h>

#include "../nettalk/protocol.h"

#define DBPATH	"./.nettalk_db"

static sqlite3 *db = NULL;
static int rgs_handler(const struct rgs_st *rcv);
int main(int argc, char **argv)
{
	int sd;
	struct sockaddr_in laddr, raddr;
	socklen_t raddrlen;
	int err, ret;
	const char *sql = NULL;
	char *errmsg = NULL;
	struct rgs_st rcvbuf;
	pid_t pid;

	//初始化套接字
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd < 0) {
		perror("socket()");
		exit(1);
	}

	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(RGS_SERVER_PORT);
	inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr);
	if (bind(sd, (void *)&laddr, sizeof(laddr)) < 0) {
		perror("bind()");
		goto ERROR1;
	}

	//创建/打开数据库
	err = sqlite3_open(DBPATH, &db);
	if (err != SQLITE_OK) {
		fprintf(stderr, "sqlite3_open() failed\n");	
		goto ERROR1;
	}
	//创建注册表
	sql = "create table if not exists rgsTable(id integer primary key autoincrement not null,\
		   count text not null, passwd text not null)";
	if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK) {
		fprintf(stderr, "sqlite3_exec():%s\n", errmsg);	
		goto ERROR2;
	}
	
	raddrlen = sizeof(raddr);
	while (1) {
		ret = recvfrom(sd, &rcvbuf, sizeof(rcvbuf), 0, (void *)&raddr, &raddrlen);	
		if (ret < 0) {
			if (errno == EINTR)
				continue;
			perror("recvfrom");
			goto ERROR2;
		}
		pid = fork();
		if (pid == 0) {
			//判断此账号是否可以注册
			/*
			 	rgs_handler 
				return value
					0 	RGS_STATUS_OK
					-1 	RGS_STATUS_FAIL
			 */
			if (rgs_handler(&rcvbuf) == 0) {
				rcvbuf.status = RGS_STATUS_OK;
			} else {
				rcvbuf.status = RGS_STATUS_FAIL;
			}
			if (sendto(sd, &rcvbuf, sizeof(rcvbuf), 0, (void *)&raddr, raddrlen) < 0) {
				perror("sendto()");
				exit(1);
			}

			exit(0);
		}
	}

	exit(0);
ERROR2:
	sqlite3_close(db);
ERROR1:
	close(sd);
	exit(1);
}

static int rgs_handler(const struct rgs_st *rcv)
{
	char *sql = NULL;
	char arr[128] = {};
	sqlite3_stmt *stmt = NULL;
	//char sql[100];
	int ret;

	//查找rgsTable中是否有rcv->count用户
	sql = "select * from rgsTable where count=?";
	//snprintf(sql, 100, "select * from rgsTable where count='%s'", rcv->count);
	//sql--->sqlite3_stmt 为了查询
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		fprintf(stderr, "sqlite3_stmt() failed\n");
		return -1;
	}
	sqlite3_bind_text(stmt, 1, rcv->count, -1, NULL);	
	/*
	 	return value:
			select
				SQLITE_ROW--->查到一条记录
				SQLITE_DONE--->执行语句没有错误，但是每查到
	 */
	ret = sqlite3_step(stmt);
	if (ret != SQLITE_ROW && ret != SQLITE_DONE) {
		fprintf(stderr, "sqlite3_step() failed\n");
		goto FAILED;
	}
	if (ret == SQLITE_ROW) {	
		//有则失败
		goto FAILED;
	}
	//无则成功　将rcv->count插入到rgsTable　并创建一个与rcv->count同名的表(存放好友)

	snprintf(arr, 128, "create table if not exists %s(id integer primary key \
		autoincrement not null, frdcount text not null)", rcv->count);
	if (sqlite3_exec(db, arr, NULL, NULL, NULL) != SQLITE_OK) {
		fprintf(stderr, "sqlite3_exec() failed\n");
		goto FAILED;
	}

	sqlite3_finalize(stmt);
	sql = "insert into rgsTable(count, passwd) values(?,?)";
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		fprintf(stderr, "sqlite3_prepare_v2() failed\n");
		return -1;
	}
	sqlite3_bind_text(stmt, 1, rcv->count, -1, NULL);	
	sqlite3_bind_text(stmt, 2, rcv->passwd, -1, NULL);	
	ret = sqlite3_step(stmt);
	if (ret != SQLITE_DONE) {
		fprintf(stderr, "sqlite3_step() failed\n");
		goto FAILED;
	}

	sqlite3_finalize(stmt);

	//将自己插入自己的好友列表
	memset(arr, '\0', 128);
	snprintf(arr, 128, "insert into %s(frdcount) values('%s')", rcv->count, rcv->count);
	if (sqlite3_exec(db, arr, NULL, NULL, NULL) != SQLITE_OK) {
		fprintf(stderr, "[%s][%d]sqlite3_exec() failed\n", __FUNCTION__, __LINE__);
		return -1;
	}


	return 0;

FAILED:
	sqlite3_finalize(stmt);
	return -1;
}


