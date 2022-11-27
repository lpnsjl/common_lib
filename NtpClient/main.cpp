/**
*Copyright (c) 2022 person.All rights reserved
*@brief 
*@author sc
*@date 2022-11-25
*@email 1752128872@qq.com
*/
#include "NTPClient.h"
#include <iostream>


int main()
{
	ntp_packet new_time_packet;
	bool flag = get_ntp_time("192.168.211.58", &new_time_packet);
	if(flag)
	{
		if(set_local_time(&new_time_packet))
		{
			std::cout << "设置本地时间成功" << std::endl;
		}
		else
		{
			std::cout << "设置本地时间失败" << std::endl;
		}
	}
	else
	{
		std::cout << "获取ntp服务时间失败" << std::endl;
	}
	return 0;
}
