/**
*Copyright (c) 2022 person.All rights reserved
*@brief 
*@author sc
*@date 2022-11-22
*@email 1752128872@qq.com
*/
#include "ftplib.h"
#include <iostream>

int main()
{
	ftplib *ftp = new ftplib();
	if(!ftp->Connect("192.168.211.58:21"))
	{
		std::cout << "连接ftp服务器失败" << std::endl;
	}
	// 该处输入ftp用户名与密码
	if(!ftp->Login("***", "***"))
	{
		std::cout << "登录ftp服务器失败" << std::endl;
	}
	if(!ftp->Nlst(nullptr, "/"))
	{
		std::cout << "列出文件目录失败" << std::endl;
	}

	return 0;
}
