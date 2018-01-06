/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：medialib.c
*   创 建 者：jshunwang
*   创建日期：2018年01月06日
*   描    述：
*
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <glob.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "medialib.h"

#define MAXCHNNUM	200
#define MAXSOGNUM	200
#define DESCRSIZE	510

//每个mp3歌曲应该具有的属性
struct song_pathname_st {
	short songid;
	char songpathname[DESCRSIZE];
}__attribute__((packed));
typedef struct song_pathname_st spath_st;

//每个频道应该具有的属性
struct channle_song_pathname_st {
	char 		chnpathname[DESCRSIZE];	//频道路径名
	short 		chnid;
	short 		songnum;
	spath_st 	songpathnames[MAXSOGNUM];	//存取该频道下的歌曲的路径名字

}__attribute__((packed)); 
typedef struct channle_song_pathname_st cspath_st;

//readchannle时标记当前位置
struct channle_posistion_st {
	short songid;
	off_t pos;
}__attribute__((packed));
typedef struct channle_posistion_st chn_pos_st;

static cspath_st chnpathnames[MAXCHNNUM] = {};
static int chnnum = 0;
static chn_pos_st cur_pos[MAXCHNNUM] = {0};//各个频道当前read的位置，数组成员下标加1是频道号

#if 1
/********************main function for test**********************/
int main(void)
{
	int i, j;
	int ret;
	int fd;
	char buf_descr[DESCRSIZE] = {}; 
	char buf_song[DESCRSIZE] = {};

	//打印频道路径信息和歌曲路径信息
	printf("*******************************test01***********************************\n");
	getchnnum();
	for(i = 0; i < chnnum; i++){
		printf("channelpath %d : %s\n", chnpathnames[i].chnid, chnpathnames[i].chnpathname);	
#if 1
		for(j = 0; j < chnpathnames[i].songnum; j++){
			printf("songpath %d: %s\n", (chnpathnames[i].songpathnames[j]).songid,\
					(chnpathnames[i].songpathnames[j]).songpathname);		
		}
#endif
	}

	//打印所有频道的描述信息
	printf("*******************************test02***********************************\n");
	for(i = 0; i < chnnum; i++){

		memset(buf_descr, '\0', DESCRSIZE);
		ret = readonechninfo( i+1, buf_descr, DESCRSIZE);
			if(ret < 0){
				perror("read chn_descr in main function");	
				return -1;
			}
		printf("channel %2d: %s\n", i+1, buf_descr);
	}

	//读取ch01的歌曲数据，存入当前文件下的tmp.mp3文件中
	printf("*******************************test03***********************************\n");
	fd = open("./tmp.mp3", O_RDWR | O_CREAT | O_TRUNC, 0664);
	if(fd < 0){
		perror("open tmp.mp3");	
		return -1;
	}

	while(1){
		ret = readchnsong( 2, buf_song, DESCRSIZE);
		if(ret < 0){
			perror("readchnsong()");
			return -1;
		}
		
		if(write(fd, buf_song, ret) < 0){
			perror("write()");
			return -1;
		}

		if(ret >= 0 && ret < DESCRSIZE){
			//break;	//读取一首歌
			printf("一首歌读取完成\n");
			sleep(2);
			printf("3秒后开始下一首\n");
			printf("3\n");
			sleep(1);
			printf("2\n");
			sleep(1);
			printf("1\n");
			sleep(1);
			printf("start\n");
			continue;	//一直循环顺序读取
		}
		
	}
	close(fd);

	return 0;
}

#endif 

//too long return 1, not return 0
static int strtoolong(const char *str)
{
	int tmp_strlen;	//字符串长度包含'\0'

	tmp_strlen = strlen(str) + 1;
	if(tmp_strlen > DESCRSIZE){
		printf("%s *** too long\n", str);
		return 1;
	}

	return 0;
}

//判断一个pathname是否是一个channel
//是返回1,不是返回0,出错返回-1
static int ischnpath(const char *path)
{
	int ret;
	void *ret_p;
	int result = 0;
	int i;
	int flag_descr = 0;
	int flag_mp3 = 0;
	glob_t tmp;
	char tmp_descr[DESCRSIZE] = {};

	memset(tmp_descr, '\0', DESCRSIZE);
	strcpy(tmp_descr, path);
	strcat(tmp_descr, "/*");
	if(strtoolong(tmp_descr)) goto err_path;
	
	ret = glob(tmp_descr, 0, NULL, &tmp);
	if(!(ret == 0 || ret == GLOB_NOMATCH)){
		printf("glob failed inischnpath : %s\n", strerror(ret));
		return -1;
	}

	for(i = 0; i < tmp.gl_pathc; i++){
		ret_p = strstr((tmp.gl_pathv)[i], ".descr");		
		if(ret_p != NULL) flag_descr = 1;
		ret_p = strstr((tmp.gl_pathv)[i], ".mp3");		
		if(ret_p != NULL) flag_mp3 = 1;
	}

	if(flag_descr && flag_mp3) result = 1;
	
	globfree(&tmp);
	return result;

err_path:
	globfree(&tmp);
	printf("the pathname is invalid\n");
	return -1;
}

int getchnnum(void)
{
	int ret;
	char tmp_descr[DESCRSIZE] = {};
	glob_t glob_chntmp;
	glob_t glob_songtmp;
	int i, m, n;

	//判断medialib路径是否太深
	memset(tmp_descr, '\0', DESCRSIZE);
	strcpy(tmp_descr, MLIBPATH);
	if(strtoolong(tmp_descr)) goto err_path;

	//获取medialib路径下的一层所有文件名（除了隐藏文件,存储在glob_chntmp中
	strcat(tmp_descr, "/*");
	if(strtoolong(tmp_descr)) goto err_path;
	ret = glob(tmp_descr, 0, NULL, &glob_chntmp);
	if(ret){
		printf("glob failed : %s\n", strerror(ret));
		return -1;
	}

	//从glob_chntmp中筛选是音乐频道的路径,并且存入chnpathnames中
	for(i = 0, m = 0; i < glob_chntmp.gl_pathc; i++){
		if(strtoolong((glob_chntmp.gl_pathv)[i])) goto err_path_g;
		
		if(ischnpath((glob_chntmp.gl_pathv)[i]) == 1){
			//如果是频道路径
				//保存频道路径名，设置频道编号
			strcpy(chnpathnames[m].chnpathname, glob_chntmp.gl_pathv[i]);
			chnpathnames[m].chnid = m + 1;
				//统计该频道下的mp3文件路径名，设置mp3文件id
					//查找当前频道下mp3文件
			memset(tmp_descr, '\0', DESCRSIZE);
			strcpy(tmp_descr, chnpathnames[m].chnpathname);
			if(strtoolong(tmp_descr)) goto err_path_g;
			strcat(tmp_descr, "/*.mp3");
			if(strtoolong(tmp_descr)) goto err_path_g;
			
			ret = glob(tmp_descr, 0, NULL, &glob_songtmp);
			if(!(ret == 0)){
				printf("glob failed for glob_songtmp: %s\n", strerror(ret));
				globfree(&glob_chntmp);
				return -1;
			}
					//赋值mp3文件路径，并配置mp3文件id
			chnpathnames[m].songnum = glob_songtmp.gl_pathc;
			for(n = 0; n < glob_songtmp.gl_pathc; n++){
				if(strtoolong((glob_songtmp.gl_pathv)[n])) goto err_path_g;
				(chnpathnames[m].songpathnames)[n].songid = n + 1;			
				strcpy((chnpathnames[m].songpathnames)[n].songpathname, (glob_songtmp.gl_pathv)[n]);
			}

			globfree(&glob_songtmp);

			chnnum ++;
			m ++;
		}
	}

	globfree(&glob_chntmp);

	return chnnum;

err_path_g:
	globfree(&glob_chntmp);
err_path:
	printf("the pathname is invalid\n");
	return -1;
}

int readonechninfo(int chnid ,void *buf, size_t count)
{
	int chn_index ;
	int ret;
	int fd;
	char chn_path[DESCRSIZE] = {};
	char buf_descr[DESCRSIZE] = {};
	glob_t gl_descr;	//存储descr文件

	chn_index = chnid -1;
	//确定频道pathname
	memset(chn_path, '\0', DESCRSIZE);
	strcpy(chn_path, (chnpathnames[chn_index].chnpathname));
	//查找“.descr”文件
	strcat(chn_path, "/*.descr");
	if(strtoolong(chn_path)) goto err_path;

	ret = glob(chn_path, 0, NULL, &gl_descr);
	if(!(ret == 0)){
		printf("glob failed for glob_chndescr: %s\n", strerror(ret));
		return -1;
	}

	//如果不止一个“descr”文件
	if(gl_descr.gl_pathc != 1){
		printf("channel %d :descr file number is invalid", chnid);	
		return -1;
	}
	
	//读取descr文件中的信息
	fd = open((gl_descr.gl_pathv)[0], O_RDONLY);
	if(fd < 0){
		perror("open chn_descr");	
		globfree(&gl_descr);
		return -1;
	}

	memset(buf_descr, '\0', DESCRSIZE);
	ret = read(fd, buf_descr, count);
	//printf("buf_descr:%s\n",buf_descr);//测试发现自带换行，没找到原因
	if(ret < 0){
		perror("read chn_descr");	
		globfree(&gl_descr);
		return -1;
	}
	memcpy(buf, buf_descr, ret);
	
	globfree(&gl_descr);
	return ret;
	
err_path:
	printf("the pathname is invalid\n");
	return -1;
}


int readchnsong(int chnid ,void *buf, size_t count)
{
	int chn_index, song_index, song_pos;
	int i, j;
	int ret;
	int fd;
	char cur_songpath[DESCRSIZE] = {};
	char buf_song[DESCRSIZE] = {};
	
	//将要read的位置
	chn_index  = chnid - 1;		//当前频道
	song_index = (cur_pos[chn_index]).songid;	//当前mp3文件
	song_pos   = (cur_pos[chn_index]).pos; 		//当前mp3文件中的位置
	
	//当前mp3文件path
	memset(cur_songpath, '\0', DESCRSIZE);
	strcpy(cur_songpath, (((chnpathnames[chn_index]).songpathnames)[song_index]).songpathname);

	//open
	fd = open(cur_songpath, O_RDONLY);
	if(fd < 0){
		perror("open mp3 file:");	
		return -1;
	}
	lseek(fd, song_pos, SEEK_SET);
	
	//read
	memset(buf_song, '\0', DESCRSIZE);
	ret = read( fd, buf_song, count);
	if(ret < 0){
		perror("read mp3 file:");	
		return -1;
	}
	
	//如果当前mp3文件读完了
	if(ret >= 0 && ret < count){
		(cur_pos[chn_index]).songid ++;
		if((cur_pos[chn_index]).songid >= (chnpathnames[chn_index]).songnum){
			(cur_pos[chn_index]).songid = 0;
		}
	
		(cur_pos[chn_index]).pos = 0;

		goto endjob;
	}
	
	//如果当前mp3文件没有读完
	(cur_pos[chn_index]).pos = lseek( fd, 0, SEEK_CUR);
	
endjob:
	//回添
	memcpy(buf, buf_song, ret);

	//close
	close(fd);

	return ret;

}







