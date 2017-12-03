/*================================================================
*   Copyright (C) 2017 Sangfor Ltd. All rights reserved.
*   
*   文件名称：medialib.c
*   创 建 者：jshunwang
*   创建日期：2017年12月01日
*   描    述：
*
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <glob.h>

#include "medialib.h"

int getchn_list(mlin_t **m, int *chnn)
{
	
	
}

int freechn_list(mlin_t **m, const int *chnn)
{
	free(*m);	
	m = NULL;
}
