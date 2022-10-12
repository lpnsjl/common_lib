/**
*Copyright (c) 2022 person.All rights reserved
*@brief 十六进制转换器, 支持小端机器, 暂不支持大端机器
*@author sc
*@date 2022-10-11
*@email 1752128872@qq.com
*/

#ifndef _HEXCONVERTER_H_
#define _HEXCONVERTER_H_
#include <iostream>
#include <string>
/*
 * @brief 十六进制字符串转float
 * */
float hex_to_float(const std::string& hex);

/*
 * @brief float转十六进制字符串
 * */
std::string float_to_hex(float f);

/*
 * @brief 十六进制字符串转double
 * */
double hex_to_double(const std::string& hex);

/*
 * @brief double转十六进制字符串
 * */
std::string double_to_hex(double d);

/*
 * @brief 十六进制字符串转int
 * */
int hex_to_int(const std::string& hex);

/*
 * @brief int转十六进制字符串
 * */
std::string int_to_hex(int i);

/*
 * @brief 十六进制字符串转unsigned int
 * */
uint32_t hex_to_uint32(const std::string& hex);

/*
 * @brief unsigned int转十六进制字符串
 * */
std::string uint32_to_hex(uint32_t i);

/*
 * @brief 十六进制字符串转int64
 * */
int64_t hex_to_int64(const std::string& hex);

/*
 * @brief int64转十六进制字符串
 * */
std::string int64_to_hex(int64_t k);

/*
 * @brief 十六进制字符串转uint64
 * */
uint64_t hex_to_uint64(const std::string& hex);

/*
 * @brief uint64转十六进制字符串
 * */
std::string uint64_to_hex(uint64_t k);

/*
 * @brief 十六进制转字符串
 * */
std::string hex_to_str(char* psrc, int srclen);

/*
 * @brief 字符串转十六进制
 * */
bool str_to_hex(std::string src, char* pdst, int dstlen);


#endif //_HEXCONVERTER_H_
