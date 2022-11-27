/**
*Copyright (c) 2022 person.All rights reserved
*@brief 
*@author sc
*@date 2022-11-25
*@email 1752128872@qq.com
*/

#include "NTPClient.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <iostream>

char protocol[32];

static int construct_packet(char *packet)
{
	char version = 1;
	long tmp_wrd;
	int port;
	time_t timer;
	strcpy(protocol, NTPV4);
	/*判断协议版本*/
	if(!strcmp(protocol, NTPV1)||!strcmp(protocol, NTPV2)||!strcmp(protocol, NTPV3)||!strcmp(protocol, NTPV4))
	{
		memset(packet, 0, NTP_PCK_LEN);
		port = NTP_PORT;
		/*设置 16 字节的包头*/
		version = protocol[5] - 0x30;
		tmp_wrd = htonl((LI << 30)|(version << 27) \
            |(MODE << 24)|(STRATUM << 16)|(POLL << 8)|(PREC & 0xff));
		memcpy(packet, &tmp_wrd, sizeof(tmp_wrd));

		/*设置 Root Delay、 Root Dispersion 和 Reference Indentifier */
		tmp_wrd = htonl(1<<16);
		memcpy(&packet[4], &tmp_wrd, sizeof(tmp_wrd));
		memcpy(&packet[8], &tmp_wrd, sizeof(tmp_wrd));
		/*设置 Timestamp 部分*/
		time(&timer);
		/*设置 Transmit Timestamp coarse*/
		tmp_wrd = htonl(JAN_1970 + (long)timer);
		memcpy(&packet[40], &tmp_wrd, sizeof(tmp_wrd));
		/*设置 Transmit Timestamp fine*/
		tmp_wrd = htonl((long)NTPFRAC(timer));
		memcpy(&packet[44], &tmp_wrd, sizeof(tmp_wrd));
		return NTP_PCK_LEN;
	}
	else if (!strcmp(protocol, TIME))/* "TIME/UDP" */
	{
		port = TIME_PORT;
		memset(packet, 0, 4);
		return 4;
	}

	return 0;
}

/*获取 NTP 时间*/
static int get_ntp_time(int sk, struct addrinfo *addr, struct ntp_packet *ret_time)
{
	fd_set pending_data;
	struct timeval block_time;
	char data[NTP_PCK_LEN * 8];
	int packet_len, data_len = addr->ai_addrlen, count = 0, result, i,re;

	/* 组织请求报文 */
	if (!(packet_len = construct_packet(data)))
	{
		return 0;
	}
	/*客户端给服务器端发送 NTP 协议数据包*/
	if ((result = sendto(sk, data, packet_len, 0, addr->ai_addr, data_len)) < 0)
	{
		perror("sendto");
		return 0;
	}
	/*调用select()函数，并设定超时时间为10s*/
	FD_ZERO(&pending_data);
	FD_SET(sk, &pending_data);
	block_time.tv_sec=2;
	block_time.tv_usec=0;
	if (select(sk + 1, &pending_data, NULL, NULL, &block_time) > 0)
	{
		/*接收服务器端的信息*/
		if ((count = recvfrom(sk, data, NTP_PCK_LEN * 8, 0, addr->ai_addr, (socklen_t*)&data_len)) < 0)
		{
			perror("recvfrom");
			return 0;
		}
		if (protocol == TIME)
		{
			memcpy(&ret_time->transmit_timestamp, data, 4);
			return 1;
		}
		else if (count < NTP_PCK_LEN)
		{
			return 0;
		}

		/* 设置接收 NTP 包的数据结构 */
		ret_time->leap_ver_mode = ntohl(data[0]);
		ret_time->startum = ntohl(data[1]);
		ret_time->poll = ntohl(data[2]);
		ret_time->precision = ntohl(data[3]);
		ret_time->root_delay = ntohl(*(int*)&(data[4]));
		ret_time->root_dispersion = ntohl(*(int*)&(data[8]));
		ret_time->reference_identifier = ntohl(*(int*)&(data[12]));
		ret_time->reference_timestamp.coarse = ntohl(*(int*)&(data[16]));
		ret_time->reference_timestamp.fine = ntohl(*(int*)&(data[20]));
		ret_time->originage_timestamp.coarse = ntohl(*(int*)&(data[24]));
		ret_time->originage_timestamp.fine = ntohl(*(int*)&(data[28]));
		ret_time->receive_timestamp.coarse = ntohl(*(int*)&(data[32]));
		ret_time->receive_timestamp.fine = ntohl(*(int*)&(data[36]));
		ret_time->transmit_timestamp.coarse = ntohl(*(int*)&(data[40]));
		ret_time->transmit_timestamp.fine = ntohl(*(int*)&(data[44]));

		/* 将NTP时间戳转换为日期 */
		time_t currentTime = ret_time->transmit_timestamp.coarse - JAN_1970;
//		std::cout << "seconds1: " << currentTime << std::endl;
		struct tm CurlocalTime;
		localtime_r(&currentTime, &CurlocalTime);
		char dateTime[30];
		strftime(dateTime, 30, "%Y-%m-%d %H:%M:%S %A", &CurlocalTime);

//		printf("%s\n", dateTime);

		return 1;
	} /* end of if select */


	return 0;
}

bool get_ntp_time(const std::string& ip, uint16_t port, struct ntp_packet *ret_time)
{
	int sockfd, rc;
	struct addrinfo hints, *res=NULL;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	rc = getaddrinfo(ip.c_str(), std::to_string(port).c_str(), &hints, &res);
	if(rc != 0)
	{
		perror("getaddrinfo");
		return false;
	}
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol); //IPv4, 数据报套接字, UDP
	if (sockfd <0 )
	{
		freeaddrinfo(res);
		perror("socket");
		return false;
	}
	int ret = get_ntp_time(sockfd, res, ret_time);
	freeaddrinfo(res);
	close(sockfd);
	return ret;
}

bool get_ntp_time(const std::string& ip, struct ntp_packet *ret_time)
{
	return get_ntp_time(ip, 123, ret_time);
}

int64_t get_timestamp(struct ntp_packet *ret_time)
{
	int64_t sec = ret_time->transmit_timestamp.coarse - JAN_1970;
	int64_t usec = USEC(ret_time->transmit_timestamp.fine);
	return (sec*1000+usec/1000);
}

/* 修改本地时间 */
bool set_local_time(struct ntp_packet * pnew_time_packet)
{
	struct timeval tv;
	tv.tv_sec = pnew_time_packet->transmit_timestamp.coarse - JAN_1970;
//	std::cout << "seconds2: " << pnew_time_packet->transmit_timestamp.coarse - JAN_1970 << std::endl;
	tv.tv_usec = USEC(pnew_time_packet->transmit_timestamp.fine);
	int ret = settimeofday(&tv, NULL);
	return !ret;
}