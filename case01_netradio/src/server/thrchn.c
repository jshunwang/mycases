/*================================================================
*   Copyright (C) 2017 Sangfor Ltd. All rights reserved.
*   
*   文件名称：thrchn.c
*   创 建 者：jshunwang
*   创建日期：2017年12月03日
*   描    述：
*
================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include "datatype.h"
#include "protocol.h"
#include "medialib.h"
	
extern int sd;
extern struct sockaddr_in raddr;



static void *thr_job(void *chid)
{
	uint8_t chnid = *((int*)chid);

	while(1){
		void *databuff = NULL;
		char song_buf[511] = {};
		databuff = calloc(1,512);
		if(NULL == databuff){
			perror("calloc");	
			exit(1);
		}
		
		((struct chnmst_st *)databuff)->chnid = chnid; 
		memset(song_buf, '\0',512);
		readchn_data(chnid, song_buf, 511);
		memcpy(((struct chnmst_st *)(databuff + 1))->msg, song_buf, 511);
		if ((sendto(sd, databuff, 512, 0, (void *)&raddr, sizeof(raddr))) < 0) {
			perror("sendto()");
			exit(1);
		}

		usleep(1000);
	}
	
	pthread_exit(0);
}

int thr_data(chnid_t chnid)
{
	pthread_t tid;
	int err;
	int chid[1] = {};
	chid[0] = chnid;

	err = pthread_create(&tid, NULL, thr_job, chid);
	printf("haha\n");
	if(err){
		fprintf(stderr, "pthread_create():%s\n",strerror(err));	
	}

	return tid;
}

