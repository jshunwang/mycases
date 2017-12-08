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
static int login_handler(const struct login_st *rcv);
int main(int argc, char **argv)
{
	int sd;
	struct sockaddr_in laddr, raddr;
	socklen_t raddrlen;
	int err, ret;
	const char *sql = NULL;
	char *errmsg = NULL;
	struct login_st rcvbuf;
	pid_t pid;

	//初始化套接字
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd < 0) {
		perror("socket()");
		exit(1);
	}

	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(LOGIN_SERVER_PORT);
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
	
	//创建一个table用于加入在线成员
	//监察和删除在线成员在chat服务端进行
	sql = "create table if not exists onlineTable(id integer primary key autoincrement not null,\
		   count text not null)";
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
			//判断此账号是否可以登录
			/*
			 	login_handler 
				return value
					0 	LOGIN_STATUS_OK
					-1 	LOGIN_STATUS_NOCNT
					-2	LOGIN_STATUS_ERRPWD
			 */
			if (login_handler(&rcvbuf) == 0) {
				rcvbuf.status = LOGIN_STATUS_OK;
			}else if(login_handler(&rcvbuf) == -1){
				rcvbuf.status = LOGIN_STATUS_NOCNT;
			}else {
				rcvbuf.status = LOGIN_STATUS_ERRPWD;
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

static int login_handler(const struct login_st *rcv)
{
	char *sql = NULL;
	char *sql2 = NULL;
	char arr[128] = {};
	char arr2[128] = {};
	sqlite3_stmt *stmt = NULL;
	sqlite3_stmt *stmt2 = NULL;
	int ret, ret2;

	//查找rgsTable中是否有rcv->count用户
	sql = "select * from rgsTable where count=?";
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

	//查找函数出错了
	if (ret != SQLITE_ROW && ret != SQLITE_DONE) {
		fprintf(stderr, "sqlite3_step() failed\n");
		goto FAILED;
	}
	//如果找到了
	if (ret == SQLITE_ROW) {
		sql2 = "select * from rgsTable where count=? and passwd=?";
		if (sqlite3_prepare_v2(db, sql2, -1, &stmt2, NULL) != SQLITE_OK) {
			fprintf(stderr, "sqlite3_stmt() failed\n");
			return -1;
		}
		sqlite3_bind_text(stmt2, 1, rcv->count, -1, NULL);	
		sqlite3_bind_text(stmt2, 2, rcv->passwd, -1, NULL);	
		ret2 = sqlite3_step(stmt2);

		//判断密码
		if(ret2	== SQLITE_ROW && ret2 != SQLITE_DONE){
			//密码正确
			memset(arr2, '\0', 128);
			snprintf(arr2, 128, "insert into onlineTable(count) values('%s')",\
					rcv->count);
			if (sqlite3_exec(db, arr2, NULL, NULL, NULL) != SQLITE_OK) {
				fprintf(stderr, "[%s][%d]sqlite3_exec() failed\n", __FUNCTION__, __LINE__);
				return -3;
			}

			sqlite3_finalize(stmt2);
			sqlite3_finalize(stmt);
			return 0;
		}else {
			//密码错误

			sqlite3_finalize(stmt2);
			sqlite3_finalize(stmt);
			return -2;
		}
	}
	//如果找不到该用户名
	if (ret == SQLITE_DONE) {
		printf("%d\n", ret);
		sqlite3_finalize(stmt);
		return -1;
	}

	return 0;

FAILED:
	sqlite3_finalize(stmt);
	return -1;
}


