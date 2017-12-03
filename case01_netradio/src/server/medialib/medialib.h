/*================================================================
*   Copyright (C) 2017 Sangfor Ltd. All rights reserved.
*   
*   文件名称：medialib.h
*   创 建 者：jshunwang
*   创建日期：2017年12月01日
*   描    述：
*
================================================================*/

#ifndef __MEDIALIB_H
#define __MEDIALIB_H

#include <stdint.h>

#define MEDIAPATH "~/share/gitrepo/mycases/case01_netradio/src/musiclib"

typedef struct mlib_list_st{
	uint8_t chnid;
	char *dsc;
}mlib_t;

/*
 	func  : 提供每个频道的描述信息
	*m    : 存储每个频道描述信息的首地址，动态开辟1024,不够截断，自加'\0'
	*chnn : 频道描述信息个数
	return: 成功返回0,失败-1.
 */
int getchn_list(mlin_t **m, int *chnn);

/*
	func  :清理getchn_list函数申请的动态空间 	
	*m    : 存储每个频道描述信息的首地址.
	*chnn : 频道描述信息个数
	return: 成功返回0,失败-1.
 */
int freechn_list(mlin_t **m, const int *chnn);



#endif



















	

 */


#endif





















