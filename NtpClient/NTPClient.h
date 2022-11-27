/**
*Copyright (c) 2022 person.All rights reserved
*@brief 
*@author sc
*@date 2022-11-25
*@email 1752128872@qq.com
*/

#ifndef _NTPCLIENT_H_
#define _NTPCLIENT_H_
#include <netdb.h>
#include <string>

#define   NTP_PORT   123
#define   TIME_PORT  37
#define   NTP_SERVER_IP  "cn.pool.ntp.org"

#define   NTP_PORT_STR   "123"
#define   NTPV1       "NTP/V1"
#define NTPV2 "NTP/V2"

#define NTPV3 "NTP/V3"
#define NTPV4 "NTP/V4"
#define TIME "TIME/UDP"

#define   NTP_PCK_LEN   48

#define LI 0
#define VN 3
#define MODE 3
#define STRATUM 0
#define POLL 4
#define PREC -6

#define JAN_1970 0x83aa7e80 /* 1900 年～1970 年之间的时间秒数 */
#define NTPFRAC(x) (4294 * (x) + ((1981 * (x)) >> 11))
#define USEC(x) (((x) >> 12) - 759 * ((((x) >> 10) + 32768) >> 16))

typedef struct _ntp_time
{
	unsigned int coarse;
	unsigned int fine;
} ntp_time;

/* NTP时钟同步报文 */
struct ntp_packet
{
	unsigned char leap_ver_mode;
	unsigned char startum;
	char poll;
	char precision;
	int root_delay;
	int root_dispersion;
	int reference_identifier;
	ntp_time reference_timestamp;
	ntp_time originage_timestamp;
	ntp_time receive_timestamp;
	ntp_time transmit_timestamp;
};

/*
 * @brief 返回ntp服务器时间
 * param[in] ip ntp服务器ip
 * param[in] port ntp服务器port
 * param[out] ret_time ntp服务器时间, 类型为ntp_packet
 * return true-成功, false-失败
 * */
bool get_ntp_time(const std::string& ip, uint16_t port, struct ntp_packet *ret_time);

/*
 * @brief 返回ntp服务器时间, 默认ntp服务端口为123
 * param[in] ip ntp服务器ip
 * param[out] ret_time ntp服务器时间, 类型为ntp_packet
 * return true-成功, false-失败
 * */
bool get_ntp_time(const std::string& ip, struct ntp_packet *ret_time);

/*
 * @brief 将ntp_packet转为时间戳
 * param[in] ret_time ntp_packet类型的时间
 * @param[out] 时间戳, 单位ms
 * */
int64_t get_timestamp(struct ntp_packet *ret_time);

/*
 * @brief 设置本地时间, 注意设置的是utc时间
 * param[in] pnew_time_packet 时间, 类型为ntp_packet
 * return true-成功, false-失败
 * */
bool set_local_time(struct ntp_packet *pnew_time_packet);


#endif //_NTPCLIENT_H_
