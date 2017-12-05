/*================================================================
*   Copyright (C) 2017 Sangfor Ltd. All rights reserved.
*   
*   文件名称：protocol.h
*   创 建 者：jshunwang
*   创建日期：2017年12月01日
*   描    述：
*			规定消息包裹的结构
*			设定默认的广播ip
================================================================*/

#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include <stdio.h>
#include "datatype.h"

#define DEFAULT_GROUP		"224.22.22.22"
#define DEFAULT_RECVPORT	 2222
#define MAXCHNNR			 200
#define MINCHNID			 1
#define MAXCHNID			 (MAXCHNNR+MINCHNID-1)
#define CHNLISTID			 0
#define MAXMSGSIZE 			 512
#define MAXDESCR			 128

//频道数据
struct chnmst_st {
	chnid_t chnid;
	char msg[1];
}__attribute__((packed));

//频道列表
//每个频道
struct listentry_st{
	chnid_t chnid;
	int8_t len;
	char descr[1];
}__attribute__((packed));

struct chnlist_st {
	chnid_t chnid;
	struct listentry_st entry[1];
}__attribute__((packed));

union msg_st{
	chnid_t chnid;

	struct chnmst_st song;
	struct chnlist_st list;
	
}__attribute__((packed));

typedef union msg_st msg_t;



#endif

