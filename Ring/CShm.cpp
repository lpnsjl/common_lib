//
// Created by andrew on 6/16/23.
//

#include "CShm.h"
#include "mkdirs.h"
#include <string.h>
#include <signal.h>
#include <stdexcept>
#include <vector>

static std::vector<std::string> gShmKeys;
static std::vector<int> gShmIDs;
static void SigHandler(int sig)
{
    for(int i=0; i<gShmIDs.size(); i++)
    {
        std::string key = gShmKeys[i];
        if(shmctl(gShmIDs[i], IPC_RMID, nullptr) == 0)
        {
            std::cout << "删除有名共享内存: " << key << std::endl;
        }
    }
    exit(0);
}


CShm::CShm(const std::string &key, uint32_t size)
:m_shmID(-1),
m_pDataPtr(nullptr),
m_sKey(key)
{
    std::string tmp = "/tmp/" + key;
    if(!mkdirs(tmp))
    {
        std::string msg = "创建目录: " + tmp + " 失败";
        throw std::logic_error(msg);
    }
    key_t id = ftok(tmp.c_str(), 0);
    if(id < 0)
    {
        std::string msg = "ftok失败: " + std::string(strerror(errno));
        throw std::logic_error(msg);
    }
    m_shmID = shmget(id, size, IPC_CREAT|0666);
    if(m_shmID < 0)
    {
        std::string msg = "shmget失败: " + std::string(strerror(errno));
        throw std::logic_error(msg);
    }
    m_pDataPtr = shmat(m_shmID, nullptr, 0);
    if(m_pDataPtr == (void*)-1)
    {
        std::string msg = "shmat失败: " + std::string(strerror(errno));
        throw std::logic_error(msg);
    }
    gShmKeys.push_back(key);
    gShmIDs.push_back(m_shmID);
    signal(SIGINT, SigHandler);
}

CShm::~CShm()
{
    if(m_pDataPtr)
    {
        shmdt(m_pDataPtr);
        if(shmctl(m_shmID, IPC_RMID, nullptr) == 0)
        {
            std::cout << "删除有名共享内存: " << m_sKey << std::endl;
        }
    }
}