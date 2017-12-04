#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>

#include "protocol.h"

int main(void)
{
	int sd;
	struct sockaddr_in myaddr, remoteaddr;
	socklen_t raddrlen;
	void *rcvbuf = NULL;
	int cnt;
	char choice = 1;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd < 0) {
		perror("socket()");
		exit(1);
	}

	//bind local address
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(DEFAULT_RECVPORT);
	//dotted-decimal---->uint32
	inet_pton(AF_INET, "0.0.0.0", &myaddr.sin_addr);
	if (bind(sd, (void *)&myaddr, sizeof(myaddr)) < 0) {
		perror("bind()");	
		goto BINDERROR;
	}

	//加入多播组
	struct ip_mreqn mrq;

	inet_aton(DEFAULT_GROUP, &mrq.imr_multiaddr);
	inet_aton("0.0.0.0", &mrq.imr_address);
	//网卡设备名---->index
	mrq.imr_ifindex = if_nametoindex("enp2s0");
	if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mrq, sizeof(mrq)) < 0) {
		perror("setsockopt()");
		goto BINDERROR;
	}

	rcvbuf = malloc(MAXMSGSIZE);
	if (NULL == rcvbuf) {
		perror("malloc()");
		goto BINDERROR;
	}

	raddrlen = sizeof(remoteaddr);
	while (1) {
		memset(rcvbuf, '\0', 512);
		if ((cnt = recvfrom(sd, rcvbuf, 512, 0, (void *)&remoteaddr, &raddrlen)) < 0) {
			perror("recvfrom()");
			goto RECVERROR;
		}

		printf("successfully recv %d bytes\n", cnt);
		printf("aaa%d\n",((msg_t *)rcvbuf)->chnid);
	
		if (((msg_t *)rcvbuf)->chnid == 0){

			int pos=1;
			for(int i =0; i < 10; i++){
				printf("intdex%d\n",i);
				printf("%d\n",((struct listentry_st *)(rcvbuf+pos))->chnid);	
				printf("%d\n",((struct listentry_st *)(rcvbuf+pos))->len);	
				printf("%s\n",((struct listentry_st *)(rcvbuf+pos))->descr);	
				pos +=(((struct listentry_st *)(rcvbuf + pos))->len);
			}	
			
		//	choice = getchar();

			continue;
		}else if(((msg_t *)rcvbuf)->chnid > 0){
			if(((msg_t *)rcvbuf)->chnid == choice){
				
				write(1, (rcvbuf+1), 511);
			}		
		}

	}

	close(sd);
	free(rcvbuf);

	exit(0);
RECVERROR:
	free(rcvbuf);
BINDERROR:
	close(sd);
	exit(1);
}

