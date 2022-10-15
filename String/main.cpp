/**
*Copyright (c) 2022 person.All rights reserved
*@brief 
*@author sc
*@date 2022-10-15
*@email 1752128872@qq.com
*/
#include <iostream>
#include "SC_string.h"

int main()
{
	// 字符串分割测试
	std::string s = ":a:&b:c:d:";
	std::string d = ":";
	auto v = split(s, d);  // v = ["", "a", "&b", "c", "d", ""]
	for(auto& x:v)
	{
		std::cout << x << " ";
	}
	std::cout << std::endl;

	std::string s1 = "&&a&&b&&c&&d&&";
	std::string d1 = "&&";
	auto v1 = split(s1, d1);  // v1 = ["", "a", "b", "c", "d", ""]
	for(auto& x:v1)
	{
		std::cout << x << " ";
	}
	std::cout << std::endl;
}