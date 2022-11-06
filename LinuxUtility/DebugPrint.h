/**
*Copyright (c) 2022 person.All rights reserved
*@brief 
*@author sc
*@date 2022-10-25
*@email 1752128872@qq.com
*/

#ifndef _DEBUGPRINT_H_
#define _DEBUGPRINT_H_
#include <stdio.h>

#define normal_info(format, ...) printf("[" __FILE__"][Line: %d][%s]: \033[32m" format"\033[32;0m\n", __LINE__, \
__func__, ##__VA_ARGS__)
#define warning_info(format, ...) printf("[" __FILE__"][Line: %d][%s]: \033[33m" format"\033[32;0m\n", __LINE__, \
__func__, ##__VA_ARGS__)
#define error_info(format, ...) printf("[" __FILE__"][Line: %d][%s]: \033[31m" format"\033[32;0m\n", __LINE__, \
__func__, ##__VA_ARGS__)

#endif //_DEBUGPRINT_H_
