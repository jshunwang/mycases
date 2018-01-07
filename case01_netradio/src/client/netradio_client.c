#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../include/protocol.h"

//用于父子进程之间用信号通知
static void handler_nothing(int s)
{

}

int main(void)
{
	int sd;
	int ret;
	struct sockaddr_in localaddr;
	struct sockaddr_in serveraddr;
	socklen_t	len_serveraddr;
	struct ip_mreqn mrq;
	char rcvbuf[MAXMSGSIZE] = {};
	int fpd[2] = {};//pipe()
	int pid;
	msg_t *tmp_msg;
	struct chnmst_st *tmp_chnmst;
	struct chninfo_st *tmp_chninfo;
	int chnnum = 0;
	int choice_chn = 0;


#if 1
/*********************************************************************
  将chnid的数据写入临时文件tmp.mp3,用于测试。
  ********************************************************************/
	int fd_mp3;

	//tmp.mp3
	fd_mp3 = open("./tmp.mp3", O_RDWR | O_CREAT | O_TRUNC, 664);
	if(fd_mp3 < 0){
		perror("open()--tmp.info");	
		close(fd_info);
		exit(1);
	}

#endif


	//socket相关
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sd < 0){
		perror("socket()");	
		exit(1);
	}

	//local ip address
	localaddr.sin_family = AF_INET;
	localaddr.sin_port 	= htons(DEFAULT_RECVPORT);
	inet_pton(AF_INET, "0.0.0.0", &localaddr.sin_addr);

	//bind
	ret = bind(sd, (void *)&localaddr, sizeof(localaddr));
	if(ret < 0){
		perror("bind()");	
		goto error_bind;	
	}
	
	//设置多播属性
	inet_aton(DEFAULT_GROUP, &mrq.imr_multiaddr);
	inet_aton("0.0.0.0", &mrq.imr_address);
	mrq.imr_ifindex = if_nametoindex("enp2s0");

	ret = setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mrq, sizeof(mrq)); 
	if(ret < 0){
		perror("setsockopt()");	
		goto error_setsock;
	}

	//准备pipe文件，用于向子进程发送数据
	if(pipe(pfd) < 0){
		perror("pipe()");
		goto error_pipe;
	}

	//注册信号行为，用于通知子进程
	signal(SIGUSR1, handler_nothing);
	
	//fork()
	pid = fork();
	if(pid == 0){
		//子进程中播放音乐文件	
		pause();
		close(pfd[1]);
		dup2(pfd[0], 0);
		execl("/bin/sh", "sh", "-c", "mplayer - -cache 5120", NULL);
		perror("execl()")
		exit(1);
	}
	
	//parents 根据用户选择的频道向子进程中写对应频道数据
	close(pfd[0]);
		//截取频道描述信息
	printf("************************** 欢 迎 使 用 mynetradio ****************************\n");
	printf("正在读取频道列表，请稍等......................................................\n");
	while(1){
		memset(rcv, '\0', MAXMSGSIZE);	
		ret = recvfrom(sd, rcvbuf, MAXMSGSIZE, 0, (void *)&serveraddr, &len_serveraddr);
		if(ret < 0){
			perror("recvfrom()");
			goto error_recv;
		}
		
		tmp_msg = (msg_t *)rcvbuf;
		chnnum = 0;
		if(tmp_msg->chnid == 0){
			tmp_chninfo = (struct chninfo_st *)tmp_msg;
			if(tmp_chninfo->chnid_chn != 1){
				continue;	
			}
			if(tmp_chninfo->chnid_chn == 0){
				printf("%-2d: %s\n", (chnnum + 1), tmp_chninfo->descr);
				break;
			}
			chnnum = chnid_chn; 
			printf("%-2d: %s\n", chnnum, tmp_chninfo->descr);

			continue;
		}
		
		usleep(100);
	}
	
	printf("请输入音乐频道标号\n");
	scanf("%d", choice_chn);
	printf("音乐即将播放，请稍等......................................................\n");
	while(1){
		memset(rcv, '\0', MAXMSGSIZE);	
		ret = recvfrom(sd, rcvbuf, MAXMSGSIZE, 0, (void *)&serveraddr, &len_serveraddr);
		if(ret < 0){
			perror("recvfrom()");
			goto error_recv;
		}
		
		tmp_msg = (msg_t *)rcvbuf;
		chnnum = 0;
		if(tmp_msg->chnid == choice_chn){
			tmp_chnmst = (struct chnmst_st *)tmp_msg;
			write(pfd[1], tmp_chnmst->msg, tmp_chnmst->len);
			//tmp.mp3 test file
			//write(fd_mp3, tmp_chnmst->msg, tmp_chnmst->len);

			continue;
		}
		
		usleep(20);
	}

	wait(NULL);
	close(pfd[1]);
	close(sd);
#if 0
	close(fd_mp3);
#endif

	return 0;

error_recv:
error_pipe:
error_setsock:
error_bind:
	close(sd);
	exit(1);
}


























