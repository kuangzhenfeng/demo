#ifndef __MY_MEMORY_POOL_H__
#define __MY_MEMORY_POOL_H__

#include <stddef.h>
#include "common.h"


class MyMemoryPoolTest : public ModuleBase
{
public:
    MyMemoryPoolTest() : ModuleBase(MODULE_MEMORY_POOL, "MODULE_MEMORY_POOL"){};
    int test();
};

class MyMemoryPool
{
public:
    MyMemoryPool();
    ~MyMemoryPool();
    static MyMemoryPool *Instance();

    void *allocate(size_t size);
    void deallocate(void *ptr, size_t size);

private:
    struct Node
    {
        struct Node *nextNode;
    };
    const int NODE_SIZE = 20;
    Node *m_memoryPool[16];
    unsigned char *m_u8FreeStart;
    unsigned char *m_u8FreeEnd;
    unsigned long long m_u64TotalAllocateSize;

    int block_allocate(size_t size);
 





};



#endif