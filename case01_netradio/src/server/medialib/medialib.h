/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：medialib.h
*   创 建 者：jshunwang
*   创建日期：2018年01月06日
*   描    述：
*
================================================================*/

#define MLIBPATH	"/home/jsw/share/gitrepo/mycases/case01_netradio/src/musiclib"

/*****************************************************************
 * 	BRIEF	:get the channels number of the medialib be associated 
 			 with MLIBPATH.
			 crate channel id and make the id associate to the uni-
			 que pathname.
 *	PARAM 	:Null
 *	RETURN	:channels number(count from 1)，fail return -1;
 ****************************************************************/
int getchnnum(void);

/*****************************************************************
 * 	BRIEF	:试图读取chnid频道内count个字节的文件描述信息，回添到
 			 buf中。
 *	PARAM 	:
 *	RETURN	:返回实际读取到的文件描述信息的字节个数，失败返回-1.
 ****************************************************************/
int readonechninfo(int chnid ,void *buf, size_t count);


/*****************************************************************
 * 	BRIEF	:循环顺序图读取chnid频道内count个字节的歌曲数据，回添到
 			 buf中。
 *	PARAM 	:
 *	RETURN	:返回实际读取到的歌曲数据的字节个数，失败返回-1.
 ****************************************************************/
int readchnsong(int chnid ,void *buf, size_t count);







