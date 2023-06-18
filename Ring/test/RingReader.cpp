//
// Created by andrew on 2023/6/18.
// Ring 读测试用例
//
#include "Ring.h"
#include <time.h>
#include <thread>
#include <iostream>

#define NS_PER_SEC 1000000000
bool stop = false;
uint64_t rxBytes = 0;
uint64_t prevRxBytes = 0;
uint64_t ns = 0;
uint64_t prevNs = 0;

uint32_t lossPacketCnt;

static void Statistic()
{
    while(!stop)
    {
        std::cout << "开始统计" << std::endl;
        struct timespec curTime;
        clock_gettime(CLOCK_MONOTONIC_RAW, &curTime);
        ns = curTime.tv_sec*NS_PER_SEC + curTime.tv_nsec;
        uint64_t diffTxBytes = rxBytes - prevRxBytes;
        uint64_t diffNS = ns - prevNs;
        prevRxBytes = rxBytes;
        prevNs = ns;
        double bps = (double)diffTxBytes / diffNS * NS_PER_SEC;
        if(bps > 1000000000)
        {
            std::cout << "rx-Bps: " << bps/1000000000 << "GB/s" << std::endl;
        }
        else if(bps > 1000000)
        {
            std::cout << "rx-Bps: " << bps/1000000 << "MB/s" << std::endl;
        }
        else if(bps > 1000)
        {
            std::cout << "rx-Bps: " << bps/1000 << "KB/s" << std::endl;
        }
        else
        {
            std::cout << "rx-Bps: " << bps << "B/s" << std::endl;
        }
        std::cout << "loss packet: " << lossPacketCnt << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

int main()
{
    std::thread t(Statistic);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    Ring ring("test1", 102400, 8192);
    uint32_t size = 1024;
    uint64_t *data = new uint64_t[size];
    uint64_t packetNum = 0;
    uint64_t prevPacketNum = 0;
    while(!stop)
    {
        uint32_t len = ring.Read((uint8_t*)data);
        if(len > 0)
        {
            packetNum = data[0];
            if(packetNum - prevPacketNum > 1)
            {
                lossPacketCnt++;
            }
            prevPacketNum = packetNum;
            rxBytes += len;
        }
    }
    t.join();
}
