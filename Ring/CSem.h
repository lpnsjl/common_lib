//
// Created by andrew on 6/16/23.
//

#ifndef RING_CSEM_H
#define RING_CSEM_H
#include <string>
#include <semaphore.h>

/**
 * 有名信号量的封装, 实现可用于进程间互斥的mutex
 */
class CSem {
public:
    /**
     * 创建有名信号量
     * @param[in] key 键值, 唯一的标识一个信号量
     */
    CSem(const std::string &key);
    ~CSem();

    void Lock();
    void UnLock();
private:
    sem_t *m_puSem;
    std::string m_sKey;
};


#endif //RING_CSEM_H
