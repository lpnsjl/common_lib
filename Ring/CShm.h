//
// Created by andrew on 6/16/23.
//

#ifndef CSHM_H
#define CSHM_H
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>


/**
 * 共享内存的简单封装
 */
class CShm
{
public:
    /**
     * 构造函数
     * @param[in] key 共享内存的唯一键值
     * @param[in] size 共享内存大小, 单位字节
     */
    CShm(const std::string &key, uint32_t size);
    ~CShm();

    /**
     * 返回共享内存指针
     * @return
     */
    void* GetPtr()
    {
        return m_pDataPtr;
    }
private:
    int32_t m_shmID;
    void *m_pDataPtr;
    std::string m_sKey;
};


#endif //CSHM_H
