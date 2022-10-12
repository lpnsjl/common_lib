/**
*Copyright (c) 2022 person.All rights reserved
*@brief 
*@author sc
*@date 2022-10-11
*@email 1752128872@qq.com
*/
#include "HexConverter.h"

float hex_to_float(const std::string& hex)
{
	union
	{
		unsigned int i;
		float f;
	}u;
	u.i = std::stoul(hex, nullptr, 16);
	float f = u.f;
	return f;
}

std::string float_to_hex(float f)
{
	union
	{
		unsigned int i;
		float f;
	}u;
	u.f = f;
	char str[9];
	int n = sprintf(str, "%x", u.i);
	std::string ret;
	ret.assign(str, str+n);
	return ret;
}

double hex_to_double(const std::string& hex)
{
	union
	{
		uint64_t i;
		double d;
	}u;
	u.i = std::stoull(hex, nullptr, 16);
	double d = u.d;
	return d;
}

std::string double_to_hex(double d)
{
	union
	{
		unsigned char c[8];
		double d;
	}u;
	u.d = d;
	char str[17];
	for(int i=0; i<8; i++)
	{
		sprintf(str+2*i, "%02x", u.c[8-i-1]);
	}
	std::string ret;
	ret.assign(str, str+16);
	return ret;
}

int hex_to_int(const std::string& hex)
{
	unsigned int i = std::stoul(hex, nullptr, 16);
	return i;
}

std::string int_to_hex(int i)
{
	char str[9];
	int n = sprintf(str, "%x", i);
	std::string ret;
	ret.assign(str, str+n);
	return ret;
}

uint32_t hex_to_uint32(const std::string& hex)
{
	uint32_t i = std::stoul(hex, nullptr, 16);
	return i;
}

std::string uint32_to_hex(uint32_t i)
{
	char str[9];
	int n = sprintf(str, "%x", i);
	std::string ret;
	ret.assign(str, str+n);
	return ret;
}

int64_t hex_to_int64(const std::string& hex)
{
	uint64_t i = std::stoull(hex, nullptr, 16);
	return i;
}

std::string int64_to_hex(int64_t k)
{
	union
	{
		unsigned char c[8];
		int64_t i;
	}u;
	u.i = k;
	char str[17];
	for(int i=0; i<8; i++)
	{
		sprintf(str+2*i, "%02x", u.c[8-i-1]);
	}
	std::string ret;
	ret.assign(str, str+16);
	return ret;
}

uint64_t hex_to_uint64(const std::string& hex)
{
	return std::stoull(hex, nullptr, 16);
}

std::string uint64_to_hex(uint64_t k)
{
	union
	{
		unsigned char c[8];
		uint64_t i;
	}u;
	u.i = k;
	char str[17];
	for(int i=0; i<8; i++)
	{
		sprintf(str+2*i, "%02x", u.c[8-i-1]);
	}
	std::string ret;
	ret.assign(str, str+16);
	return ret;
}

std::string hex_to_str(char* psrc, int srclen)
{
	int bytesize = 2;
	char* dst = new char[srclen*bytesize+1];
	for( int i = 0; i < srclen; i++ )
		sprintf( dst + i * bytesize, "%02X", (unsigned char)psrc[i] );
	std::string ret = dst;
	delete[] dst;
	return ret;
}

bool str_to_hex(std::string src, char* pdst, int dstlen)
{
	int srclen = src.size();
	if( dstlen < srclen / 2 )
		return false;

	for( int idx = 0; idx < srclen; idx += 2 )
	{
		sscanf( src.c_str() + idx, "%2hhx", pdst + idx / 2 ); //%2hhx,hhx只匹配2个字符
	}

	return true;
}