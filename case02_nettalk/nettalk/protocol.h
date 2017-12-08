#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

#define DEFAULT_SERVER_IP  "172.25.2.122"

#define BUFSIZE			    256

/*
	register
*/
#define RGS_SERVER_IP		DEFAULT_SERVER_IP
#define RGS_SERVER_PORT		2221
enum{
	RGS_STATUS_OK,
	RGS_STATUS_FAIL
};

struct rgs_st{
	char count[BUFSIZE];
	char passwd[BUFSIZE];
	int8_t status;
}__attribute__((packed));

/*
	login
*/
#define LOGIN_SERVER_IP 	DEFAULT_SERVER_IP
#define LOGIN_SERVER_PORT	2222
enum{
	LOGIN_STATUS_OK,
	LOGIN_STATUS_NOCNT,
	LOGIN_STATUS_ERRPWD
};

struct login_st{
	char count[BUFSIZE];
	char passwd[BUFSIZE];
	int8_t status;
}__attribute__((packed));

/*
	add friend
*/
#define ADDFRD_SERVER_IP	DEFAULT_SERVER_IP
#define ADDFRD_SERVER_PORT	2223
enum{
	ADDFRD_STATUS_OK,
	ADDFRD_STATUS_NOEXIT,
	ADDFRD_STATUS_ALREADY
};
struct addfrd_st{
	char src_count[BUFSIZE];
	char dst_count[BUFSIZE];
	int8_t status;
}__attribute__((packed));

/*
	chat
*/
#define CHAT_SERVER_IP		DEFAULT_SERVER_IP
#define CHAT_SERVER_PORT	2224
enum{
	MSG_ADDFRD,
	MSG_CHAT
};

struct chat_st{
	char src_count[BUFSIZE];
	char dst_count[BUFSIZE];
	char msg[BUFSIZE];
	int8_t msgtype;
}__attribute__((packed));

#endif // PROTOCOL_H
