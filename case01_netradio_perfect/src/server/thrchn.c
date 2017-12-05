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
#include <sys/wait.h>
#include <sys/socket.h>
#include <pthread.h>
#include <sched.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "datatype.h"
#include "protocol.h"
#include "medialib.h"
	
extern int sd;
extern struct sockaddr_in raddr;
extern pthread_mutex_t mut_senddata;


static void *thr_job(void *chnid)
{
	chnid_t chnid_ = (chnid_t)chnid;
	int flag = 0;	
//	int fd_test;
//	fd_test = open("./test2.mp3", O_RDWR | O_CREAT | O_TRUNC, 666);

	while(flag > -1){
		flag ++;
		void *databuff = NULL;
		char song_buf[511] = {};
		int cnt_r = 0;
		databuff = calloc(1,512);
		if(NULL == databuff){
			perror("calloc");	
			exit(1);
		}
		
		((struct chnmst_st *)databuff)->chnid = chnid_; 
		memset(song_buf, '\0',512);
		//单首循环
		if((cnt_r = readchn_data(chnid_, song_buf, 511)) == 0) continue;

		//单首一次
	//	if((cnt_r = readchn_data(chnid_, song_buf, 511)) == 0) break;
		memcpy(((struct chnmst_st *)(databuff))->msg, song_buf, cnt_r);
		pthread_mutex_lock(&mut_senddata);
		if ((sendto(sd, databuff, cnt_r + 1, 0, (void *)&raddr, sizeof(raddr))) < 0) {
			perror("sendto()");
			exit(1);
		}
		pthread_mutex_unlock(&mut_senddata);
		if(chnid_ == 2 || chnid_ == 1){
			printf("###%d######################################################\n",\
					((struct chnmst_st *)databuff)->chnid );
#if 0
			char *tmp = databuff;
			for(int i=1; i<=511;i++){
				printf("%c",tmp[i]);
			}
			printf("\n");
#endif
		//	write(fd_test, (tmp+1), cnt_r);
		}

		sched_yield();
		usleep(3898);
		free(databuff);
	}
	
	pthread_exit(0);
}

int thr_songdata(chnid_t chnid)
{
	pthread_t tid;
	int err;

	err = pthread_create(&tid, NULL, thr_job, (chnid_t *)chnid);
	//printf("haha\n");
	if(err){
		fprintf(stderr, "pthread_create():%s\n",strerror(err));	
	}

	return tid;
}

