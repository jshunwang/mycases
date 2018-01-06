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
#include <stdint.h>

typedef uint8_t chnid_t;

#define DEFAULT_GROUP		"224.22.22.22"	//广播组ip
#define DEFAULT_RECVPORT	 2222			//广播进程端口
#define MAXCHNNR			 200				//最大广播频道数目
#define MINCHNID			 1				//最小广播频道id
#define MAXCHNID			 (MAXCHNNR+MINCHNID-1)	//最大广播频道id
#define CHNLISTID			 0				//频道列表信息id
#define MAXMSGSIZE 			 512			//单次网络传输字节数目（总数）
#define RSONGSIZE 		 	 510			//试图读取歌曲文件字节数目
#define MAXDESCR			 510			//描述说明信息最大字节个数
#define RDESCRSIZE			 510			//试图读取一个频道信息文件的字节个数

//频道内歌曲数据,因为MP3是流式文件，不需要结束标志，按循环顺序传输即可
struct chnmst_st {
	chnid_t chnid;	//标记频道所属
	short	len; 	//标记valid信息长度
	char msg[510];	//固定传输长读510个字节数据信息，包含valid信息和'\0'
}__attribute__((packed));

//一个频道的描述信息，用len=0,descr=NULL，做为最后结束的标志
struct chninfo_st{
	chnid_t chnid;
	short 	len;
	char descr[510];
}__attribute__((packed));

//发送接收的网络数据
union msg_st{
	chnid_t chnid;

	struct chnmst_st song;
	struct chninfo_st chninfo;
	
}__attribute__((packed));

//将发送接收的网络数据定义成一个类型
typedef union msg_st msg_t;

#endif

