/*================================================================
*   Copyright (C) 2017 Sangfor Ltd. All rights reserved.
*   
*   文件名称：medialib.h
*   创 建 者：jshunwang
*   创建日期：2017年12月03日
*   描    述：
*
================================================================*/

#ifndef __MEDIALIB_H
#define __MEDIALIB_H

#include "datatype.h"

#define MUSICPATH "/home/jsw/share/gitrepo/mycases/case01_netradio/src/musiclib/"

typedef struct mlib_list_st {
	chnid_t chnid;
	char *dsc;
}mlib_t;


int getchn_list(mlib_t **m, int *chnn);
int freechn_list(mlib_t **m, const int *chnn);

ssize_t readchn_data(chnid_t chnid,  void *buf, size_t size);

#endif

