#include <iostream>
#include <iomanip>
#include <sstream>
#include "TimeStamp.h"


int main()
{
	// 获取时间戳, 以ms为单位
	time_t timestamp = get_timeStamp();
	std::cout << "timestamp: " << timestamp << std::endl; // timestamp: 1665791915902

	// 时间戳转字符串格式日期
	std::string s = timestamp_to_str(timestamp);  // 2022-10-15 07:58:35
	std::cout << s << std::endl;

	// 字符串格式日期转时间戳
	std::cout << str_to_timestamp(s.c_str()) << std::endl;  // 1665791915

	return 0;
}
