//
// Created by andrew on 2022/10/5.
//

#ifndef ASIO_TEST_TIMERQUEUE_H
#define ASIO_TEST_TIMERQUEUE_H
#include <stdint.h>
#include <functional>
#include <atomic>
#include <chrono>
#include <thread>
#include <set>
#include <mutex>
#include <iostream>
#include "ThreadPool.h"

namespace SC
{
	/*
	 * 获取当前时间戳, 单位ms
	 * */
	time_t getTimeStamp();

	typedef std::function<void(void)> TimerCallBack;
class Timer: public std::enable_shared_from_this<Timer>
	{
	public:
		typedef uint64_t TimerID;

		Timer();
		~Timer();
		void SetCallBack(TimerCallBack callback) {callback_ = callback;}
		void SetInterval(int interval) {interval_ = interval;}
		void SetRepeat(bool repeat) {repeat_ = repeat;}
		TimerID id() {return id_;}
		bool repeat() {return repeat_;}
		int64_t interval() {return interval_;}
		void run();
	private:
		static std::atomic<TimerID> sg_id_;  // 全局id
		TimerID id_;
		TimerCallBack callback_;
		int interval_;  // // 定时器触发的时间间隔, 单位ms
		bool repeat_;  // true-定时器重复触发, false-定时器触发一次
	};



	class TimerQueue
	{
	public:
		/*
		 * @brief 构造函数
		 * @param[in] thread_nums, 设置定时器队列的工作线程数量; 默认为0, 由定时器队列主线程负责处理定时器回调函数
		 * */
		TimerQueue(uint32_t thread_nums=0);
		~TimerQueue();

		/*
		 * brief 添加定时器
		 * @param[in] cb 定时器触发时的回调函数
		 * @param[in] interval 触发间隔, 单位ms
		 * @param[in] repeat true-定时器重复触发, false-定时器触发一次, 默认为true
		 * @param[in] is_runnow, true-立刻触发定时器回调函数, false-等待interval后触发定时器回调函数, 默认为true
		 * @param[out] 定时器id, 可用于取消该定时器
		 * */
		Timer::TimerID AddTimer(TimerCallBack cb, int interval, bool repeat=true, bool is_runnow=true);

		/*
		 * brief 取消定时器
		 * @param[in] id 定时器id
		 * */
		void CancelTimer(Timer::TimerID id);

		/*
		 * brief 设置tick, 单位ms
		 * */
		void SetTick(int tick){tick_ = tick;}
	private:
		typedef std::pair<int64_t, std::shared_ptr<Timer>> Entry;
		typedef std::set<Entry> TimerList;

		/*
		 * brief 启动定时器队列循环
		 * */
		void Loop();

		uint32_t thread_nums_;  // 线程数量
		ThreadPool pool_;  // 线程池
		TimerList timer_list_;
		std::mutex mutex_;
		int tick_;
		std::shared_ptr<std::thread> th_;
		std::atomic<bool> stop_;
	};
}



#endif //ASIO_TEST_TIMERQUEUE_H
