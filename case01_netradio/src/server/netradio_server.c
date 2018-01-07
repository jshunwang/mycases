/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：mainserver.c
*   创 建 者：jshunwang
*   创建日期：2018年01月07日
*   描    述：
*
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unsitd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netiner/in.h>
#include <arpa/inet.h>
#include <net/if.h>

#include "../include/protocol.h"
#include "./medialib/medialib.h"
#include "./thrsend/thrsend.h"


int main(void)
{
	int ret;
	int chnnum = 0;
	chnid_t chn, chnid;
	int sd;
	struct ip_mreqn mrq; 
	struct sockaddr_in raddr;
	msg_t msg_data;
	sdad_st sdad;

	//初始化本地medialib
	chnnum = getchnnum();
	if(chnnum < 0){
		fprintf(stderr, "getchnnum() failed\n");
		return -1;
	}

	//初始化多线程并发锁
	thrsend_init();

	//初始化套接字
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sd < 0){
		perror("socket()");
		exit(1);
	}

	//将sd设置为广播属性
	inet_aton(DEFAULT_GROUP, &mrq.imr_multiaddr);	
	inet_aton("0.0.0.0", &mrq.imr_address);
	mrq.imr_ifindex = if_nametoindex("wlp3s0");

	ret = setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, &mrq, sizeof(mrq));
	if(ret < 0){
		perror("setsockopt()");	
		close(sd);
		exit(1);
	}

	//整理server端ip信息
	raddr.sin_family = AF_INET;
	raddr.sin_port	 = htons(DEFAULT_RECVPORT);
	inet_aton(DEFAULT_GROUP, &raddr.sin_addr);
	sdad.sd = sd;
	sdad.raddr = raddr;

	//多线程发送meidialib数据
	for(chnid = 0; chnid < (chnnum + 1); chnid++, chnid %= (chnnum + 1)){
		//read and send channel infomation
		if(chnid == 0){
		msgdata = (struct chninfo_st)msgdata;
			for(chn = 1; chn <= chnnum; chn ++){
				msgdata.chnid = 0;
				msgdata.chnid_chn = chn % chnnum;//注意最后一个频道的标号是0,可作为结束标志
				memset(msgdata.descr, '\0', MAXDESCR);
				ret = readonechninfo( chn, msgdata.descr, MAXDESCR);
				if(ret < 0){
					perror("readonechninfo()");	
					exit(1);
				}
				msgdata.len	= ret;
				ret = thrsend(sdad, chnid, msgdata.descr, msgdata.len);
				if(ret < 0){
					perror("thrsend()");	
					exit(1);
				}
			}
			usleep(200000);//频道信息不要发太频繁
		}	
		//read and send song data
		msgdata = (struct chnmst_st)msgdata;
		msgdata.chnid = chnid;
		msgdata.nothing = 0;
		memset(msgdata.msg, '\0', MAXDESCR);
		ret = readchnsong(chnid, msgdata.msg, MAXDESCR);
		if(ret < 0){
			perror("readchnsong()");	
			exit(1);
		}
		msgdata.len	= ret;
		ret = thrsend(sdad, chnid, msgdata.descr, msgdata.len);
		if(ret < 0){
			perror("thrsend()");	
			exit(1);
		}	


	}
	
	colse(sd);
	return 0;
}























