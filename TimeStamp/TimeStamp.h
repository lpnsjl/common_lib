/**
*Copyright (c) 2022 person.All rights reserved
*@brief 
*@author sc
*@date 2022-10-14
*@email 1752128872@qq.com
*/
#include <iostream>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <string>
#include <chrono>
#include <cstdio>

#ifndef _TIMESTAMP_H_
#define _TIMESTAMP_H_
// 获取时间戳(毫秒级)
time_t get_timeStamp();
/*
 * brief 将时间戳转换为字符串格式的日期; 转换以本机时区为准, 如果本机是上海时区, 则转换为上海时间的日期; 如果主机是utc时区, 则转换为utc时间的日期
 * @param[in] timestamp 时间戳, 单位ms
 * @param[in] format 转换格式, 默认"%Y-%m-%d %H:%M:%S", 详细信息参考README.md
 * @param[out] 字符串格式时间
 * */
std::string timestamp_to_str(long long timestamp, const std::string& format="%Y-%m-%d %H:%M:%S");

/*
 * brief 字符串格式日期转时间戳; 与本机时区无关, 即无论本机是什么时区, 得到的时间戳都是按照标准定义的时间戳(自1970-1-1开始所经过的秒数)
 * @param[in] str 字符串格式日期
 * @param[in] fmt 转换格式, 默认"%Y-%m-%d %H:%M:%S", 详细信息参考README.md
 * @param[out] 时间戳, 单位为s
 * */
template<typename CHAR>
uint64_t str_to_timestamp(const CHAR* str, const CHAR* fmt = "%Y-%m-%d %H:%M:%S")
{
	std::basic_istringstream<CHAR> is(str);
	std::tm tm = {};
	is >> std::get_time(&tm, fmt);

	return std::mktime(&tm);
}
#endif //_TIMESTAMP_H_
