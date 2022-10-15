/**
*Copyright (c) 2022 person.All rights reserved
*@brief 
*@author sc
*@date 2022-10-14
*@email 1752128872@qq.com
*/
#include "TimeStamp.h"

time_t get_timeStamp()
{
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
	time_t timestamp = tmp.count();
	//std::time_t timestamp = std::chrono::system_clock::to_time_t(tp);
	return timestamp;
}

static std::tm *gettm(long long timestamp)
{
	auto milli = timestamp;
	auto mTime = std::chrono::milliseconds(milli);
	auto tp = std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>(mTime);
	auto tt = std::chrono::system_clock::to_time_t(tp);
	std::tm *now = localtime(&tt);
	return now;
}

std::string timestamp_to_str(long long timestamp, const std::string& format)
{
	std::tm *t = gettm(timestamp);
	char s[100];
	strftime(s, sizeof(s), format.c_str(), t);
	return s;
}