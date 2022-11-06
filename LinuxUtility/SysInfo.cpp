/**
*Copyright (c) 2022 person.All rights reserved
*@brief 
*@author sc
*@date 2022-10-26
*@email 1752128872@qq.com
*/

#include "SysInfo.h"
#include <iostream>
#include <string.h>
#include <cpuid.h>
#include "DebugPrint.h"

#define BUFSIZE 1024

bool GetMemUsage(int& usage)
{
	FILE* fp;
	char buf[BUFSIZE];
	fp = fopen("/proc/meminfo", "r");
	if(fp == nullptr)
	{
		error_info("open /proc/meminfo failed");
		return false;
	}
	fgets(buf, sizeof(buf), fp);
	char name1[64];
//	char name2[64];
	long total_mem = 0;
	sscanf(buf, "%s %ld", name1, &total_mem);
	fgets(buf, sizeof(buf), fp);
	fgets(buf, sizeof(buf), fp);
	long free_mem = 0;
	sscanf(buf, "%s %ld", name1, &free_mem);
	usage = (total_mem-free_mem)*100.0/total_mem;
	fclose(fp);
	return true;
}

bool getCurrentDownloadRates(const std::string& if_name,long int * save_rate,long int * tx_rate)
{
	FILE * net_dev_file;    //文件指针
	char buffer[1024];  //文件中的内容暂存在字符缓冲区里
	size_t bytes_read;  //实际读取的内容大小
	char * match;    //用以保存所匹配字符串及之后的内容
	int counter = 0;
	int i = 0;
	char tmp_value[128];

	if((NULL == if_name.c_str())||(NULL == save_rate)||(NULL == tx_rate))
	{
		error_info("uncorrect param");
		return false;
	}

	if ( (net_dev_file=fopen("/proc/net/dev", "r")) == NULL ) //打开文件/pro/net/dev/，我们要读取的数据就是它啦
	{
		error_info("open file /proc/net/dev/ error!");
		return false;
	}
	memset(buffer,0,sizeof(buffer));

	while(fgets(buffer,sizeof(buffer),net_dev_file) != NULL)
	{
		match = strstr(buffer,if_name.c_str());

		if(NULL == match)
		{
			continue;
		}
		else
		{
			//printf("%s\n",buffer);
			match = match + strlen(if_name.c_str()) + strlen(":");/*地址偏移到冒号*/
			sscanf(match,"%ld ",save_rate);
			memset(tmp_value,0,sizeof(tmp_value));
			sscanf(match,"%s ",tmp_value);
			match = match + strlen(tmp_value);
			for(i=0;i<strlen(buffer);i++)
			{
				if(0x20 == *match)
				{
					match ++;
				}
				else
				{
					if(8 == counter)
					{
						sscanf(match,"%ld ",tx_rate);
					}
					memset(tmp_value,0,sizeof(tmp_value));
					sscanf(match,"%s ",tmp_value);
					match = match + strlen(tmp_value);
					counter ++;
				}
			}
		}
	}
	fclose(net_dev_file);
	return true;/*返回成功*/
}

bool GetNetSpeed(const std::string& if_name, NetSpeed& speed)
{
	int64_t start_rcv_bytes = 0;
	int64_t end_rcv_bytes = 0;
	int64_t start_tx_bytes = 0;
	int64_t end_tx_bytes = 0;

	bool success = getCurrentDownloadRates(if_name.c_str(), &start_rcv_bytes, &start_tx_bytes);
	if(!success)
	{
		return false;
	}
	usleep(500*1000);
	success = getCurrentDownloadRates(if_name.c_str(), &end_rcv_bytes, &end_tx_bytes);
	if(!success)
	{
		return false;
	}
	speed.down_rate = (end_rcv_bytes-start_rcv_bytes)*8*2;
	speed.up_rate = (end_tx_bytes - start_tx_bytes)*8*2;
	return true;
}

bool GetCpuTem(double& temp)
{
	FILE* fp;
	int tmp;
	char buf[BUFSIZE];
	fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
	if(fp == nullptr)
	{
		return false;
	}

	fgets(buf, sizeof(buf), fp);
	sscanf(buf, "%d", &tmp);
	temp = tmp / 1000.0;
	fclose(fp);
	return true;
}

typedef  struct CPU_PACKED
{
	char name[20];
	unsigned int user;
	unsigned int nice;
	unsigned int system;
	unsigned int idle;
}CPU_OCCUPY;
static bool GetCpuOccupy(CPU_OCCUPY* cpust)
{
	FILE* fp;
	fp = fopen("/proc/stat", "r");
	if(fp== nullptr)
	{
		error_info("cannot open /proc/stat");
		return false;
	}
	char buf[BUFSIZE];
	fgets(buf, sizeof(buf), fp);
	sscanf(buf, "%s %u %u %u %u", cpust->name, &cpust->user, &cpust->nice, &cpust->system, &cpust->idle);
	fclose(fp);
	return true;
}

bool GetCpuUsage(int& usage)
{
	CPU_OCCUPY cpu_occupy1;
	CPU_OCCUPY cpu_occupy2;

	bool success = GetCpuOccupy(&cpu_occupy1);
	if(!success)
	{
		return false;
	}
	usleep(500*1000);
	success = GetCpuOccupy(&cpu_occupy2);
	if(!success)
	{
		return false;
	}
	uint32_t od, nd, id, sd;
	od = cpu_occupy1.user + cpu_occupy1.nice + cpu_occupy1.system + cpu_occupy1.idle;
	nd = cpu_occupy2.user + cpu_occupy2.nice + cpu_occupy2.system + cpu_occupy2.idle;

	id = cpu_occupy2.user - cpu_occupy1.user;
	sd = cpu_occupy2.system - cpu_occupy2.system;
	if((nd-od) != 0)
	{
		usage = (sd+id)*100.0/(nd-od);
	}
	else
	{
		usage = 0;
	}
	return true;
}