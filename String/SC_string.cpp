/**
*Copyright (c) 2022 person.All rights reserved
*@brief 
*@author sc
*@date 2022-10-15
*@email 1752128872@qq.com
*/
#include "SC_string.h"

std::vector<std::string> split(const std::string& s, const std::string& d)
{
	std::vector<std::string> v;
	std::string::const_iterator start=s.begin();
	std::string::const_iterator pos = s.begin();
	while((pos = std::search(start, s.end(), d.begin(), d.end()))!=s.end())
	{
		v.emplace_back(std::move(std::string(start, pos)));
		pos += d.size();
		start = pos;
	}
	v.emplace_back(std::move(std::string(start, pos)));
	return v;
}