/*================================================================
*   Copyright (C) 2017 Sangfor Ltd. All rights reserved.
*   
*   文件名称：medialib.c
*   创 建 者：jshunwang
*   创建日期：2017年12月03日
*   描    述：
*
================================================================*/

#include <stdio.h>
#include <glob.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

#include "medialib.h"
#include "datatype.h"


int getchn_list(mlib_t **m, int *chnn)
{
	int ret;
	int cnt_r;
	int fd;
	glob_t despathbuff;
	char mediades_path[512] = {};
	int pathlen;
	char desbuff[128] = {};

	pathlen = 2 + strlen(MUSICPATH) + strlen("*/*.descr");
	if(pathlen > 512){
		goto ERROR1;	
	}	
	strcpy(mediades_path,MUSICPATH);	
	strcat(mediades_path, "*/*.descr");
	glob(mediades_path, 0, NULL, &despathbuff);	

	for(int i = 0; i < despathbuff.gl_pathc; i++){
		m[i] = calloc(1,sizeof(mlib_t));
		if(NULL == m[i]){
			perror("calloc");	
			exit(1);
		}

		m[i]->chnid = i+1;
		m[i]->dsc = calloc(1, 128);
		if(NULL == m[i]){
			perror("calloc");	
			exit(1);
		}
		
		fd = open((despathbuff.gl_pathv)[i], O_RDONLY);
		cnt_r = read(fd, desbuff, 127);		
		close(fd);
		strcpy(m[i]->dsc, desbuff);
	}

	*chnn = despathbuff.gl_pathc;

	globfree(&despathbuff);

	return 0;

ERROR1:
	printf("the mdeialib pathname is too long\n");
	exit(0);
}



int freechn_list(mlib_t **m, const int *chnn)
{
	for(int i = 0; i < *chnn; i++){
		free(m[i]->dsc);	
		free(m[i]);
	}	
	*m = NULL;

	return 0;
}



ssize_t readchn_data(chnid_t chnid, void *buf, size_t size)
{
	//test code
	int cnt_r;
	int fd;
	static off_t offset1 = 0;
	static off_t offset2 = 0;


	if(chnid == 1){
		fd = open("/home/jsw/share/gitrepo/mycases/case01_netradio/src/musiclib/music_ch01/0b海阔天空.mp3",O_RDONLY );
		cnt_r= pread(fd, buf, size, offset1);
		offset1 += cnt_r;
		if(cnt_r < size){
			offset1 = 0;	
		}
	}else if(chnid == 2){
		fd = open("/home/jsw/share/gitrepo/mycases/case01_netradio/src/musiclib/music_ch02/a千年之恋.mp3",O_RDONLY);
		//fd = open("/etc/passwd",O_RDONLY);
		cnt_r= pread(fd, buf, size, offset2);
		offset2 += cnt_r;
		if(cnt_r < size){
			offset2 = 0;	
		}
	}
	close(fd);





#if 0
	int pathlen;
	char mediamp3_path[512] = {};
	glob_t mp3pathbuff;
	DIR *path_chn;
	struct dirent *readf_curr;
	char songpath[512] = {};
	int fd_r;
	int cnt_r;
	char song_buf[1024] = {};
	static long pos_dir = 0;
	static off_t pos_mp3 = 0;



	pathlen = 2 + strlen(MUSICPATH) + strlen("*");
	if(pathlen > (512-128)){
		goto ERROR1;	
	}	
	strcpy(mediamp3_path,MUSICPATH);	
	strcat(mediamp3_path, "*");
	glob(mediamp3_path, 0, NULL, &mp3pathbuff);	
#if 0
	for(int i = 0; i < mp3pathbuff.gl_pathc; i++){
		puts((mp3pathbuff.gl_pathv)[i]);
	}
#endif
	
	path_chn = opendir(mp3pathbuff.gl_pathv[chnid-1]);
	if(NULL == path_chn){
		perror("pendir");
		exit(1);	
	}
	while(1){
	//	printf("%ld\n",pos_dir);
	//	sleep(1);
		seekdir(path_chn, pos_dir);
		readf_curr = readdir(path_chn);	
		errno = 0;
		if(NULL == readf_curr && errno == 0){
			rewinddir(path_chn);
			pos_dir = 0;
	//	puts((mp3pathbuff.gl_pathv)[chnid-1]);
			continue;	
		}
			
		if(NULL != strstr(readf_curr->d_name,"mp3")){
			printf("%s\n",readf_curr->d_name);
			strcpy(songpath, mp3pathbuff.gl_pathv[chnid-1]);
			strcat(songpath, "/");
			strcat(songpath, readf_curr->d_name);
			fd_r = open(songpath, O_RDONLY);
			if(-1 == fd_r){
				perror("open()");	
				exit(1);
			}
			while(1){
			//	printf("pos_mp3:%ld\n", pos_mp3);
				lseek(fd_r, pos_mp3, SEEK_SET);
				cnt_r = read(fd_r, song_buf, size);	
				close(fd_r);
				if(0 == cnt_r){
					pos_mp3 = 0;
					pos_dir +=telldir(path_chn);
					break;
				}
				if(-1 == cnt_r){
					perror("read()");	
					exit(1);
				}
				pos_mp3 += cnt_r;
				memcpy(buf, song_buf, cnt_r);	
				break;
			}
			
			break;
		}else{
			pos_dir +=telldir(path_chn);
			continue;	
		}
	}
	closedir(path_chn);
	
#endif
	return	cnt_r;

ERROR1:
	printf("the mdeialib pathname is too long\n");
	exit(0);
}
