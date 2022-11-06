/**
*Copyright (c) 2022 person.All rights reserved
*@brief 
*@author sc
*@date 2022-10-26
*@email 1752128872@qq.com
*/

#ifndef _SYSINFO_H_
#define _SYSINFO_H_

#include <unistd.h>
#include <iostream>

/***获取网速***/
struct NetSpeed
{
	int64_t up_rate;  // 上传网速, 单位bps
	int64_t down_rate;  // 下载网速, 单位bps
};
bool getCurrentDownloadRates(const std::string& if_name,long int * save_rate,long int * tx_rate);
bool GetNetSpeed(const std::string& if_name, NetSpeed& speed);

/***获取内存使用率***/
/*
 * @brief 获取内存占用率
 * @param[out] usage 内存占用率, 单位%
 * @return true-成功, false-失败
 * */
bool GetMemUsage(int& usage);

/***获取cpu序列号***/

/***获取cpu温度***/
/*
 * @brief 获取cpu温度
 * @param[out] temp 温度值
 * @return true-成功, false-失败
 * */
bool GetCpuTem(double& temp);

/***获取cpu使用率***/
/*
 * @brief 获取cpu使用率
 * @param[out] usage cpu使用率, 单位%
 * @return true-成功, false-失败
 * */
bool GetCpuUsage(int& usage);

#endif //_SYSINFO_H_
