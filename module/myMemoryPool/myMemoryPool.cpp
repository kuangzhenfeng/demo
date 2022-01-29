#include "myMemoryPool.h"
#include <stdlib.h>
#include <string.h>
#include "common.h"

MyMemoryPool::MyMemoryPool()
{
    m_u8FreeStart = NULL;
    m_u8FreeEnd = NULL;
    m_u64TotalAllocateSize = 0;
    memset(m_memoryPool, 0, sizeof(m_memoryPool));
}

MyMemoryPool::~MyMemoryPool()
{

}

MyMemoryPool *MyMemoryPool::Instance()
{
    static MyMemoryPool instance;
    return &instance;
}

void *MyMemoryPool::allocate(size_t size)
{
    if(size > 128)
    {
        DEBUG("Size is %lu, use std operator new", size);
        return operator new(size);
    }
    size = (size + 8 - 1) & ~(8 - 1 );  // 8倍向上取整 或用size = (size + 8 - 1) - (size + 8 - 1) % 8;
    Node *&headNode = m_memoryPool[(size - 1) / 8];
    if(NULL == headNode)
    {
        // 首个节点为空，表示未分配内存，需进行内存分配
        block_allocate(size);
    }
    Node *curNode = headNode;
    headNode = headNode->nextNode;
    DEBUG("operator new address is %p", curNode);
    return (void *)curNode;
}

int MyMemoryPool::block_allocate(size_t size)
{
    void *pRes = NULL;
    size_t freeSize = m_u8FreeEnd - m_u8FreeStart;
    Node *&headNode = m_memoryPool[(size - 1) / 8];
    if(0 == freeSize)
    {
        DEBUG("size=%lu, freeSize=%lu, operator new", size, freeSize);
        freeSize = size * NODE_SIZE * 2 + (m_u64TotalAllocateSize >> 4);
        freeSize = (freeSize + 8 - 1) & ~(8 - 1);    // 8倍向上取整
        DEBUG("new_size=%lu, m_u64TotalAllocateSize=%llu", freeSize, m_u64TotalAllocateSize + freeSize);
        m_u8FreeStart = (unsigned char *)operator new(freeSize);
        m_u8FreeEnd = m_u8FreeStart + freeSize;
        m_u64TotalAllocateSize += freeSize;
        return block_allocate(size);
    }
    else if(freeSize < size)
    {
        DEBUG("freeSize=%lu < size=%lu, move", freeSize, size);
        m_memoryPool[(freeSize - 1) / 8] = (Node *)m_u8FreeStart;
        m_memoryPool[(freeSize - 1) / 8]->nextNode = NULL;
        m_u8FreeStart = m_u8FreeEnd;
        return block_allocate(size);
    }
    headNode = (Node *)m_u8FreeStart;
    Node *curNode = headNode;
    DEBUG("freeSize=%ld", freeSize);
    for(int i = 0; i < NODE_SIZE - 1; ++i)
    {   
        if(m_u8FreeEnd - m_u8FreeStart < size * 2)
        {
            break;
        }
        curNode->nextNode = (Node *)((unsigned char *)curNode + size);         // 移动n字节需先将类型转换为unsigned char *
        curNode = curNode->nextNode;
        m_u8FreeStart += size;
    }
    curNode->nextNode = NULL;
    m_u8FreeStart += size;
    DEBUG("freeSize=%ld", m_u8FreeEnd - m_u8FreeStart);
    return 0;
}

void MyMemoryPool::deallocate(void *ptr, size_t size)
{
    if(size > 128)
    {
        DEBUG("Size is %lu, use std free", size);
        return free(ptr);
    }
    size = (size + 8 - 1) & ~(8 - 1 );  // 8倍向上取整 或用size = (size + 8 - 1) - (size + 8 - 1) % 8;
}