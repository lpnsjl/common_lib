//
// Created by andrew on 6/16/23.
//

#ifndef RING_RING_H
#define RING_RING_H
#include <string>
#include "CShm.h"
#include "CSem.h"
#include "barrier.h"

/**
 * 高性能无锁Ring, 支持单生产者多消费者, 适用于多进程
 */
class Ring
{
public:
    struct BlockParam
    {
        uint32_t flag;  // 标识共享内存是否已被创建, 共享内存被创建后, flag置为2^32-1
        uint32_t unBlockNum;
        uint32_t unBlockSize;
    };

    struct BlockHeader
    {
        uint64_t unWriteIndex;  // 当前块的写位置
        uint32_t unLen;  // 块有效数据长度
    };

    /**
     * 构造函数
     * @param[in] key Ring的唯一标识
     * @param[in] BlockNum 块数量
     * @param[in] BlockSize 块大小
     */
    Ring(const std::string &sKey, uint32_t unBlockNum, uint32_t unBlockSize);
    ~Ring();

    /**
     * 写入数据
     * @param[in] pSrc 源数据指针
     * @param[in] unSize 源数据大小, 单位字节
     * @return 写入数据大小
     */
    uint32_t Write(const uint8_t* pSrc, uint32_t unSize);

    /**
     * 读数据
     * @param[out] pDst 目的数据指针
     * @return 实际读到数据的大小, 单位字节
     */
    uint32_t Read(uint8_t *pDst);

private:
    uint8_t *m_pData;
    uint64_t m_unReadIndex;  // 读索引, 每个进程都拥有自己的读索引
    uint64_t m_unWriteIndex;  // 写索引
    BlockParam *m_pstBlockParam;
    CShm *m_pShm rte_aligned(64);
    CSem *m_pSem rte_aligned(64);
};


#endif //RING_RING_H
