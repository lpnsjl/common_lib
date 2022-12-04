/**
*Copyright (c) 2022 person.All rights reserved
*@brief 
*@author sc
*@date 2022-12-04
*@email 1752128872@qq.com
*/

#include "mkdirs.h"
#include <cstring>

int _sysmkdir(const std::string& dir)
{
	int ret = mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if (ret && errno == EEXIST)
	{
		printf("dir[%s] already exist.\n", dir.c_str());
	}
	else if (ret)
	{
		printf("create dir[%s] error: %d %s\n", dir.c_str(), ret, strerror(errno));
		return -1;
	}
	else
	{
		printf("create dir[%s] success.\n", dir.c_str());
	}
	return 0;
}
std::string __getParentDir(const std::string& dir)
{
	std::string pdir = dir;
	if (pdir.length() < 1)
	{
		return "";
	}
	while (pdir.length() > 1 && (pdir[pdir.length() - 1] == '/')) pdir = pdir.substr(0, pdir.length() - 1);

	pdir = pdir.substr(0, pdir.find_last_of('/'));
	return pdir;
}
int _sysmkdirs(const std::string& dir)
{
	int ret = 0;
	if (dir.empty())
		return -1;
	std::string pdir;
	if ((ret = _sysmkdir(dir)) == -1)
	{
		pdir = __getParentDir(dir);
		if ((ret = _sysmkdirs(pdir)) == 0)
		{
			ret = _sysmkdirs(dir);
		}
	}
	return ret;
}

bool mkdirs(const std::string& dir)
{
	int ret = _sysmkdirs(dir);
	return !ret;
}
