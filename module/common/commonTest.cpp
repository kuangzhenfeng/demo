#include "commonTest.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <thread>
#include "common.h"
#include "myNeuron.h"
#include "myThreadPoolThird.h"
#include "myMemoryPool.h"
#include "myThreadPool.h"
#include "myIOMultiplexing.h"
#include "myJson.h"
#include "mySmartPointer.h"
#include "myProtobuf.h"
#include "mySocket.h"
#include "myIPC.h"
#include "myConditionVariable.h"
#include "myReactor.h"
#include "mySTL.h"

CommonTest::CommonTest()
{
    moduleMap.insert(std::make_pair(MODULE_NEURON, std::make_shared<MyNeuronTest>()));
    moduleMap.insert(std::make_pair(MODULE_THREAD_POOL_THIRD, std::make_shared<MyThreadPoolThirdTest>()));
    moduleMap.insert(std::make_pair(MODULE_MEMORY_POOL, std::make_shared<MyMemoryPoolTest>()));
    // moduleMap.insert(std::make_pair(MODULE_THREAD_POOL, std::make_shared<MyThreadPoolTest>()));
    moduleMap.insert(std::make_pair(MODULE_IO_MULTIPLEXING, std::make_shared<MyIOMultiplexingTest>()));
    moduleMap.insert(std::make_pair(MODULE_JSON, std::make_shared<MyJsonTest>()));
    moduleMap.insert(std::make_pair(MODULE_SMART_POINTER, std::make_shared<MySmartPointerTest>()));
    moduleMap.insert(std::make_pair(MODULE_PROTOBUF, std::make_shared<MyProtobufTest>()));
    moduleMap.insert(std::make_pair(MODULE_SOCKET, std::make_shared<MySocketTest>()));
    moduleMap.insert(std::make_pair(MODULE_IPC, std::make_shared<MyIPCTest>()));
    moduleMap.insert(std::make_pair(MODULE_CONDITION_VARIABLE, std::make_shared<MyConditionVariableTest>()));
    moduleMap.insert(std::make_pair(MODULE_REACTOR, std::make_shared<MyReactorTest>()));
    moduleMap.insert(std::make_pair(MODULE_STL, std::make_shared<MySTLTest>()));
}

int CommonTest::test(MODULE_TYPE_E moduleType)
{
    auto itr = moduleMap.find(moduleType);
    if(itr == moduleMap.end())
    {
        MYLOG(LEVEL_ERROR, "Invalid module type, moduleType=%d", moduleType);
        return -1;
    }
    MYLOG(LEVEL_INFO, "module test, moduleName=%s", itr->second->getName().c_str());
    std::thread t([itr](){ itr->second->test(); });
    t.detach();
    return 0;
}

int CommonTest::testAll()
{
    for(auto &item : moduleMap)
    {
        MYLOG(LEVEL_INFO, "module test, moduleName=%s", item.second->getName().c_str());
        std::thread t([&](){ item.second->test(); });
        t.detach();
    } 
    return 0;
}
