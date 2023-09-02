#ifndef __MY_TEST_BASE_H__
#define __MY_TEST_BASE_H__

#include "testBase.h"

typedef enum
{
    MODULE_NEURON,              // 神经网络
    MODULE_THREAD_POOL_THIRD,   // 第三方线程池
    MODULE_MEMORY_POOL,         // 内存池
    MODULE_THREAD_POOL,         // 线程池
    MODULE_IO_MULTIPLEXING,     // IO多路复用
    MODULE_JSON,                // JSON
    MODULE_SMART_POINTER,       // 智能指针
    MODULE_PROTOBUF,            // protobuf
    MODULE_SOCKET,              // socket
    MODULE_IPC,                 // 进程间通信
    MODULE_CONDITION_VARIABLE,  // 条件变量
    MODULE_REACTOR,             // Reactor网络模型
    MODULE_STL,                 // STL

    MODULE_MAX
} MODULE_TYPE_E;

class ModuleBase : public TestBase
{
public:
    ModuleBase(MODULE_TYPE_E type, std::string name) : m_type(), m_name(name) {};
    virtual ~ModuleBase(){};
    const MODULE_TYPE_E &getType() { return m_type; }
    const std::string &getName() { return m_name; }

private:
    MODULE_TYPE_E m_type{};
    std::string m_name{};
};

#endif