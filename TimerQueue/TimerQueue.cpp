//
// Created by andrew on 2022/10/5.
//

#include "TimerQueue.h"
#include <vector>
#include <iterator>

namespace SC
{
	//
	time_t getTimeStamp()
	{
		auto tp =
			std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());
		auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
		time_t timestamp = tmp.count();
		return timestamp;
	}

	// class Timer
	std::atomic<Timer::TimerID> Timer::sg_id_(0);

	Timer::Timer()
		: callback_(nullptr),
		  repeat_(false),
		  interval_(1000),
		  id_(sg_id_++)
	{
		std::cout << "create timer: timer id is " << id_ << std::endl;
	}

	Timer::~Timer()
	{
		std::cout << "cancel timer: timer id is " << id_ << std::endl;
	}

	void Timer::run()
	{
		if (callback_)
		{
			callback_();
		}
	}

	// class TimerQueue
	TimerQueue::TimerQueue(uint32_t thread_nums)
		: thread_nums_(thread_nums),
		  pool_(thread_nums),
		  th_(new std::thread(&TimerQueue::Loop, this)),
		  tick_(1),
		  stop_(false)
	{

	}

	TimerQueue::~TimerQueue()
	{
		stop_.store(true);
		if (th_->joinable())
		{
			th_->join();
		}
		// 清空定时器队列
		timer_list_.clear();
	}

	Timer::TimerID TimerQueue::AddTimer(SC::TimerCallBack cb, int interval, bool repeat, bool is_runnow)
	{
		std::unique_lock<std::mutex> lock(mutex_);
		auto timer = std::make_shared<Timer>();
		timer->SetCallBack(cb);
		timer->SetInterval(interval);
		timer->SetRepeat(repeat);
		{
			uint64_t t;
			if (is_runnow)
			{
				t = getTimeStamp();
			}
			else
			{
				t = getTimeStamp() + interval;
			}
			Entry tmp(t, timer);
			timer_list_.insert(tmp);
		}
		return timer->id();
	}

	// todo: 提升取消定时器效率到log(N)时间复杂度
	void TimerQueue::CancelTimer(Timer::TimerID id)
	{
		std::unique_lock<std::mutex> lock(mutex_);
		auto iter = timer_list_.begin();
		while (iter != timer_list_.end())
		{
			if (iter->second->id() == id)
			{
				iter = timer_list_.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

	void TimerQueue::Loop()
	{
		while (!stop_.load())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(tick_));
			int64_t now = getTimeStamp();
			std::vector<Entry> expires;
//			std::shared_ptr<Timer> t(reinterpret_cast<Timer*>(UINTPTR_MAX));

			Entry tmp(now, nullptr);
			{
				std::unique_lock<std::mutex> lock(mutex_);
				auto end = timer_list_.lower_bound(tmp);
				std::copy(timer_list_.begin(), end, std::back_inserter(expires));
				timer_list_.erase(timer_list_.begin(), end);
				
				// 重启定时器或取消定时器
				for (auto& x : expires)
				{
					auto timer = x.second;
					if (timer->repeat())
					{
						Entry e(timer->interval() + now, timer);
						std::unique_lock<std::mutex> lock(mutex_);
						timer_list_.insert(e);
					}
				}
			}
			// ִ执行回调函数
			for (auto& x : expires)
			{
				if (thread_nums_ == 0)
				{
					x.second->run();
				}
				else
				{
					pool_.enqueue(std::bind(&Timer::run, x.second));
				}
			}
		}
	}
}