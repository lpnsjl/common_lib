/**
*Copyright (c) 2022 person.All rights reserved
*@brief 
*@author sc
*@date 2022-10-13
*@email 1752128872@qq.com
*/
#include "TimerQueue.h"

void print1()
{
	std::cout << "print1....." << std::endl;
}

void print2()
{
	std::cout << "print2....." << std::endl;
}

void print3()
{
	std::cout << "print3....." << std::endl;
}

void print4()
{
	std::cout << "print4...." << std::endl;
}

int main()
{
	SC::TimerQueue timer_queue_(1);
	// 添加定时器, 立马运行, 重复触发
	auto id1 = timer_queue_.AddTimer(print1, 1000, true, true);
	// 添加定时器, 1s后触发, 只触发一次
	auto id2 = timer_queue_.AddTimer(print2, 1000, false, false);
	// 添加定时器, 1s后运行, 重复触发
	auto id3 = timer_queue_.AddTimer(print3, 1000, true, false);
	// 添加定时器, 立马运行, 只触发一次
	auto id4 = timer_queue_.AddTimer(print4, 1000, false, true);
	while(true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(5));
		timer_queue_.CancelTimer(id1);
		break;
	}
}