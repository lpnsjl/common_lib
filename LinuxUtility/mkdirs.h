/**
*Copyright (c) 2022 person.All rights reserved
*@brief 递归创建多级目录，支持Linux平台
*@author sc
*@date 2022-12-04
*@email 1752128872@qq.com
*/

#ifndef _MKDIRS_H_
#define _MKDIRS_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>

int _sysmkdir(const std::string& dir);
std::string __getParentDir(const std::string& dir);
int _sysmkdirs(const std::string& dir);

/*
 * @brief 递归创建目录
 * param[in] dir 目录名
 * return true-创建成功, false-创建失败
 * */
bool mkdirs(const std::string& dir);


#endif //_MKDIRS_H_
