/*================================================================
*   Copyright (C) 2017 Sangfor Ltd. All rights reserved.
*   
*   文件名称：main.c
*   创 建 者：jshunwang
*   创建日期：2017年12月03日
*   描    述：
*
================================================================*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <pthread.h>
#include <sched.h>
#include "medialib.h"
#include "thrchn.h"
#include "thrlist.h"
#include "datatype.h"
#include "protocol.h"



int sd;
struct sockaddr_in raddr;

int main(void)
{

	int chnnr;
	mlib_t *list[MAXCHNNR] = {};
	getchn_list(list, &chnnr);
	freechn_list(list, &chnnr);
	
#if 0	
	
	//test:getchn_list();
	int chnnr;
	mlib_t *list[MAXCHNNR] = {};
	getchn_list(list, &chnnr);
	for(int i = 0; i < chnnr; i++){
		printf("id: %d  %s\n",list[i]->chnid, list[i]->dsc);
	}
	freechn_list(list, &chnnr);
#endif

#if 0
	//test:readchn_dat()
	char song_buf[512] = {};
	while(1){
		memset(song_buf, '\0', 512);
		readchn_data(1, song_buf, 512);
		write(1,song_buf,512);
		usleep(1000);
	}
#endif
#if 1
	//初始化套接字
	
	sd = socket(AF_INET,SOCK_DGRAM,0);
	if(sd < 0){
		perror("socket()");	
		exit(1);
	}

	struct ip_mreqn mrq;
	inet_aton(DEFAULT_GROUP, &mrq.imr_multiaddr);
	inet_aton("0.0.0.0",&mrq.imr_address);

	mrq.imr_ifindex = if_nametoindex("enp2s0");
	if(setsockopt(sd,IPPROTO_IP,IP_MULTICAST_IF,&mrq,sizeof(mrq)) < 0){
		perror("setsockopt()");	
		close(sd);
		exit(1);
	}

	raddr.sin_family =AF_INET;
	raddr.sin_port = htons(DEFAULT_RECVPORT);
	inet_aton(DEFAULT_GROUP, &raddr.sin_addr);
#endif

	//thrlist();
#if 1
//	thr_list();



#endif

#if 1
	chnid_t i;
	for( i = 0; i <= 2; i++){
		if(i == 0){
			thr_list();
		}else {
			thr_songdata(i);
		}
	}

		pause();
#endif
	pause();
	exit(0);


}
