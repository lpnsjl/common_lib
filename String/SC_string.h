/**
*Copyright (c) 2022 person.All rights reserved
*@brief 
*@author sc
*@date 2022-10-15
*@email 1752128872@qq.com
*/

#ifndef _SC_STRING_H_
#define _SC_STRING_H_
#include <string>
#include <vector>
#include <algorithm>

/*
 * brief 字符串分割函数, 根据分割字符将字符串分成若干块
 * @param[in] s 待分割的源字符串
 * @param[in] d 分割符
 * @return 分割后的字符串向量
 * */
std::vector<std::string> split(const std::string& s, const std::string& d);

#endif //_SC_STRING_H_
