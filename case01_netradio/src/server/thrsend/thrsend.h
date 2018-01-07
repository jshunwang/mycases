/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：thrsend.h
*   创 建 者：jshunwang
*   创建日期：2018年01月07日
*   描    述：
*
================================================================*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

struct sd_ipaddress_st {
	int sd;
	struct sockaddr_in raddr;
	
}__attribute__((packed));
typedef sd_ipdaddress_st sdad_st;

/*****************************************************************
 * 	BRIEF	:创建一个线程，向一个已经创建报式的套接字sdad(sd 和ip地址)中试图发送
 			 下标为index的buf中的size个字节数据。原子操作。
 *	PARAM 	:index < 200
 *	RETURN	:返回新建线程id，失败返回-1.
 ****************************************************************/
int thrsend(sdad_st sdad, short index, const char *buf, int size);

/*****************************************************************
 * 	BRIEF	:使用本头文件中的其他函数前需要调用一次thrsend_init(),
 			只用一次就好。
 *	PARAM 	:size <= 512
 *	RETURN	:成功返回0，不失败.
 ****************************************************************/
int thrsend_init(void);


















