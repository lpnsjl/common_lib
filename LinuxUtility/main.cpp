/**
*Copyright (c) 2022 person.All rights reserved
*@brief 
*@author sc
*@date 2022-10-25
*@email 1752128872@qq.com
*/
#include <iostream>
#include "DebugPrint.h"
#include "SysInfo.h"

int main()
{
	/*获取网络速度测试*/
//	while(1)
//	{
//		NetSpeed speed{};
//		bool success = GetNetSpeed("ens33", speed);
//		std::cout << "down rate: " << speed.down_rate << ", up rate: " << speed.up_rate<<std::endl;
//	}
	/*内存使用率测试*/
//	int mem_usage = 0;
//	bool success = GetMemUsage(mem_usage);
//	if(success)
//	{
//		std::cout << "mem usage: " << mem_usage << "%" << std::endl;
//	}

	/*获取cpuid*/
//	std::cout << "cpuid: " << GetCpuId() << std::endl;

	/***获取cpu使用率***/
	while(1)
	{
		int cpu_usage = 0;
		if(GetCpuUsage(cpu_usage))
		{
			std::cout << "cpu usage: " << cpu_usage << "%" << std::endl;
		}
	}
	return 0;
}