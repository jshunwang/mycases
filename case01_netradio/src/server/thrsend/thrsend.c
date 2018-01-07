/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：thrsend.c
*   创 建 者：jshunwang
*   创建日期：2018年01月07日
*   描    述：
*
================================================================*/

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#include "thrsend.h"

#define MAXINDEXNUM		200	//index最大数目
#define MAXBUFSIZE		514

struct send_arg_st {
	short 	index;
	int    	bufsize;
	char	buf[MAXBUFSIZE];
}__attribute__((packed));
typedef send_arg_st sarg_st;

static sdad_st sdads[MAXINDEXNUM] = {};	//用于存放相应index的sd
static pthread_mutex_t mut_sds[MAXINDEXNUM];	//对sds中的sd加互斥锁


#if 0
/*********************main() for test thrsend.c******************/

int main(void)
{
	

	return 0;
}


#endif

//初始化sds的互斥锁
int thrsend_init(void)
{
	return pthread_mutex_init( mut_sds, NULL);
}

//定义线程行为函数thr_job
//发送数据，加锁解锁
static void *thr_job(void *arg)
{
	int ret;
	sarg_st sarg;

	sarg.index = ((sarg_st *)arg)->index; 
	sarg.bufsize = ((sarg_st *)arg)->bufsize;
	memset(sarg.buf, '\0', MAXBUFSIZE);
	memcpy(sarg.buf, ((sarg_st *)arg)->buf, sarg.bufsize);

	//发送
	pthread_mutex_lock(&(mut_sds[sarg.index]));
	
	ret = sendto((sdads[sarg.index]).sd, sarg.buf, sarg.bufsize, 0,\
				(void *)(sdads[sarg.index]).raddr, sizeof((sdads[sarg.index]).raddr));
	if(ret < 0){
		perror("sendto()");	
		exit(1);
	}

	pthread_mutex_unlock(&(mut_sds[sarg.index]));
	usleep(3898);
	
	pthread_exit(0);
}

//提供外部借口，创建线程
int thrsend(sdad_st sdad, short index, const char *buf, int size)
{
	int ret;
	short index_;
	pthread_t tid;
	sarg_st	sarg;

	index_ = index;

	sdads[index_] = sdad;
	
	sarg.index = index_;
	sarg.bufsize = size;
	memset(sarg.buf, '\0', MAXBUFSIZE);
	memcpy(sarg.buf, buf, sarg.bufsize);
	
	//创建线程
	ret = pthread_create(&tid, NULL, thr_job, &sarg);
	if(ret){
		fprintf(stderr, "pthread_create():%s\n", strerror(ret));	
	}

	return tid;
}



















