//
// Created by andrew on 2023/6/18.
// Ring 写测试用例
//
#include "Ring.h"
#include <time.h>
#include <unistd.h>
#include <thread>
#include <iostream>

#define NS_PER_SEC 1000000000
bool stop = false;
uint64_t txBytes = 0;
uint64_t prevTxBytes = 0;
uint64_t ns = 0;
uint64_t prevNs = 0;

static void Statistic()
{
    while(!stop)
    {
        std::cout << "开始统计" << std::endl;
        struct timespec curTime;
        clock_gettime(CLOCK_MONOTONIC_RAW, &curTime);
        ns = curTime.tv_sec*NS_PER_SEC + curTime.tv_nsec;
        uint64_t diffTxBytes = txBytes - prevTxBytes;
        uint64_t diffNS = ns - prevNs;
        prevTxBytes = txBytes;
        prevNs = ns;
        double bps = (double)diffTxBytes / diffNS * NS_PER_SEC;
        if(bps > 1000000000)
        {
            std::cout << "tx-Bps: " << bps/1000000000 << "GB/s" << std::endl;
        }
        else if(bps > 1000000)
        {
            std::cout << "tx-Bps: " << bps/1000000 << "MB/s" << std::endl;
        }
        else if(bps > 1000)
        {
            std::cout << "tx-Bps: " << bps/1000 << "KB/s" << std::endl;
        }
        else
        {
            std::cout << "tx-Bps: " << bps << "B/s" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

int main()
{
    std::thread t(Statistic);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    Ring ring("test1", 20480, 8192);
    uint32_t size = 40;
    uint64_t *data = new uint64_t[size];
    uint64_t k = 0;
    while(!stop)
    {
        data[0] = k;
        txBytes += ring.Write((uint8_t*)data, size*sizeof(uint64_t));
        k++;
        if(k % 2000 == 0)
        {
            usleep(1);
        }
    }
    t.join();
}