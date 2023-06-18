//
// Created by andrew on 6/16/23.
//

#include "Ring.h"
#include <string.h>
#include <iostream>
#include "barrier.h"
#include "CShm.h"
#include "CSem.h"


/**
 * 计算最接近2的最大幂次方
 * @param x
 * @return
 */
static uint32_t RoundUpPowOfTwo(uint32_t x)
{
    uint32_t ret = 1;
    while(ret < x)
    {
        ret = ret << 1;
    }
    return ret;
}

Ring::Ring(const std::string &sKey, uint32_t unBlockNum, uint32_t unBlockSize):
m_pShm(nullptr),
m_pData(nullptr),
m_pstBlockParam(nullptr),
m_pSem(nullptr),
m_unReadIndex(0)
{
    unBlockNum = RoundUpPowOfTwo(unBlockNum);
    m_pSem = new CSem(sKey);
    // 申请共享内存
    m_pSem->Lock();
    m_pShm = new CShm(sKey, sizeof(BlockParam)+unBlockNum*(unBlockSize+sizeof(BlockHeader)));
    m_pstBlockParam = (BlockParam*)m_pShm->GetPtr();
    if(m_pstBlockParam->flag != UINT32_MAX)
    {
        std::cout << "创建共享内存, 将共享内存数据全置零" << std::endl;
        memset(m_pShm->GetPtr(), 0, sizeof(BlockParam)+unBlockNum*(unBlockSize+sizeof(BlockHeader)));
        m_pstBlockParam->flag = UINT32_MAX;
        m_pstBlockParam->unBlockNum = unBlockNum;
        m_pstBlockParam->unBlockSize = unBlockSize;
        m_pstBlockParam->unWriteIndex = 0;
    }
    m_pSem->UnLock();
    m_unReadIndex = m_pstBlockParam->unWriteIndex;
    m_pData = (uint8_t*)(m_pstBlockParam+1);
}

Ring::~Ring()
{
    delete m_pShm;
    delete m_pSem;
}

uint32_t Ring::Write(const uint8_t *pSrc, uint32_t unSize)
{
    if(unlikely(pSrc == nullptr || unSize > m_pstBlockParam->unBlockSize))
    {
        std::string msg = "无效的参数, pSrc为空指针或写入大小大于块大小";
        throw std::logic_error(msg);
    }
    uint32_t mask = m_pstBlockParam->unBlockNum - 1;
    uint32_t offset = m_pstBlockParam->unWriteIndex & mask;
    auto p = m_pData + offset*(m_pstBlockParam->unBlockSize+sizeof(BlockHeader));
    BlockHeader *header = (BlockHeader*)p;
    header->unLen = unSize;
    memcpy(p+sizeof(BlockHeader), pSrc, unSize);
    rte_smp_wmb();
    m_pstBlockParam->unWriteIndex++;
    return unSize;
}

uint32_t Ring::Read(uint8_t *pDst)
{
    uint32_t l = m_pstBlockParam->unWriteIndex - m_unReadIndex;
    // 无数据可读
    if(l < 1)
    {
        return 0;
    }
    uint32_t mask = m_pstBlockParam->unBlockNum - 1;
    uint32_t offset = m_unReadIndex & mask;
    auto p = m_pData + offset*(m_pstBlockParam->unBlockSize+sizeof(BlockHeader));
    BlockHeader *header = (BlockHeader*)p;
    uint32_t size = header->unLen;
    memcpy(pDst, p+sizeof(BlockHeader), size);
    rte_smp_wmb();
    m_unReadIndex++;
    return size;
}