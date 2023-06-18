//
// Created by andrew on 6/16/23.
//

#include "CSem.h"
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <vector>
#include <cerrno>
#include <cstring>
#include <stdexcept>
#include "mkdirs.h"

static std::vector<std::string> gKeys;
static void SigHandler(int sig)
{
    // ctrl+c 删除信号量
    for(auto iter = gKeys.begin(); iter != gKeys.end(); ++iter)
    {
        if(sem_unlink((*iter).c_str()) == 0)
        {
            std::cout << "删除有名信号量: " << *iter << std::endl;
        }
    }
    exit(0);
}


CSem::CSem(const std::string &key)
:m_puSem(nullptr),
m_sKey(key)
{
    m_puSem = sem_open(key.c_str(), O_CREAT|O_RDWR, 0666, 1);
    if(!m_puSem)
    {
        std::string msg = "sem_open失败: " + std::string(strerror(errno));
        throw std::logic_error(msg);
    }
    // 记录信号量信息, 当ctrl+c时, 删除有名信号量
    gKeys.push_back(key);
    signal(SIGINT, SigHandler);
    signal(SIGKILL, SigHandler);
    signal(SIGTERM, SigHandler);
}

CSem::~CSem()
{
    if(m_puSem)
    {
        sem_close(m_puSem);
        if(sem_unlink(m_sKey.c_str()) == 0)
        {
            std::cout << "删除有名信号量: " << m_sKey << std::endl;
        }
    }
}

void CSem::Lock()
{
    sem_wait(m_puSem);
}

void CSem::UnLock()
{
    sem_post(m_puSem);
}