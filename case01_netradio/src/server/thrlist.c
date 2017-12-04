/*================================================================
*   Copyright (C) 2017 Sangfor Ltd. All rights reserved.
*   
*   文件名称：thrlist.c
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



static void *thr_job(void *s)
{
	int len_tmp = 1;

	struct chnlist_st *listdescrp;
	int chnnr;
	mlib_t *list[MAXCHNNR] = {};

	

	getchn_list(list, &chnnr);

#if 0
	//检查	
	for(int i = 0; i < chnnr; i++){
		printf("id: %d  %s\n",list[i]->chnid, list[i]->dsc);
	}
#endif
	void *listbuff = NULL;
	listbuff = calloc(1,512);
	if(NULL == listbuff){
		perror("calloc");	
		exit(1);
	}
	((struct chnlist_st *)listbuff)->chnid = 0; 
	((struct listentry_st *)(listbuff + 1))->chnid = 1;
	((struct listentry_st *)(listbuff + 1))->len = 1+1+strlen(list[0]->dsc)+1;
	memcpy(((struct listentry_st *)(listbuff + 1))->descr, list[0]->dsc,strlen(list[0]->dsc)+1);
	printf("bb\n");

	for(int i = 1; i < chnnr; i++){
		len_tmp += strlen(list[i]->dsc)+3;
		printf("cc\n");
		((struct listentry_st*)(listbuff + len_tmp))->chnid = i+1;
		((struct listentry_st*)(listbuff + len_tmp))->len = strlen(list[i]->dsc) + 3;
		memcpy(((struct listentry_st*)(listbuff + len_tmp))->descr,\
			list[i]->dsc, strlen(list[i]->dsc)+1);
	printf("dd\n");
	}

	if(len_tmp > 512){
		printf("too long\n");	
		exit(1);
	}

	while(1){

#if 0
		//test:listpackage
		printf("type:%d\n",((msg_t *)listbuff)->chnid);
		int pos=1;
		for(int i =0; i < chnnr; i++){
			printf("intdex%d\n",i);
			printf("%d\n",((struct listentry_st *)(listbuff+pos))->chnid);	
			printf("%d\n",((struct listentry_st *)(listbuff+pos))->len);	
			printf("%s\n",((struct listentry_st *)(listbuff+pos))->descr);	
			pos +=(((struct listentry_st *)(listbuff + pos))->len);
		}		
#endif
		
		if ((sendto(sd, listbuff, 512, 0, (void *)&raddr, sizeof(raddr))) < 0) {
			perror("sendto()");
			exit(1);
		}


		sleep(1);	
	}
	
	freechn_list(list, &chnnr);
	pthread_exit(0);
}

int thr_list(void)
{
	pthread_t tid;
	int err;

	err = pthread_create(&tid, NULL, thr_job, NULL);
	printf("haha\n");
	if(err){
		fprintf(stderr, "pthread_create():%s\n",strerror(err));	
	}

	return tid;
}

