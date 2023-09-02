//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_set>
#include <memory>
#include <bitset>
#include "common.h"
#include "commonTest.h"

#include "../../../main/backtrace_dump.h"


#if 0
void print()
{
}

template <typename T, typename... TYPES>
void print(const T &firstArg, const TYPES &...args)
{
    std::cout << firstArg << std::endl;
    std::cout << "size: " << sizeof...(args) << std::endl;
    print(args...);
}

template<typename ...T> class tuple;    // 为什么要做转发声明

template<>
class tuple<> {};                   // 不做转发声明会报错：‘tuple’ is not a class template

template<typename Head, typename ...Tail>
class tuple<Head, Tail...> : private tuple<Tail...>
{
    typedef tuple<Tail...> inherited;
public:
    tuple() {}
    tuple(Head head, Tail... tail) : m_head(head), inherited(tail...) {}

    Head head() { return m_head; }
    inherited &tail() { return *this; }

protected:
    Head m_head;
};
#endif

#include <list>
#include <queue>
#include <chrono>
using namespace std::chrono;

int main()
{
    mylog::LogManager::Instance()->setDisplayLevel(LEVEL_ALL);
    // CommonTest::Instance()->test(MODULE_THREAD_POOL_THIRD);
    // CommonTest::Instance()->test(MODULE_STL);
    // CommonTest::Instance()->test(MODULE_IPC);
    CommonTest::Instance()->test(MODULE_SOCKET);
    // CommonTest::Instance()->test(MODULE_THREAD_POOL);
    
    while(1)
        sleep(1);
    return 0;
#if 1
    // int a = 1;
    // char str[] = "abc123";
    // mylog::LogManager::Instance()->setDisplayLevel(LEVEL_ALL ^ LEVEL_DEBUG ^ LEVEL_INFO);
    mylog::LogManager::Instance()->setDisplayLevel(LEVEL_ALL);
    // MYLOG(LEVEL_FATAL, "a=%d", a);
    // MYLOG(LEVEL_ERROR, "a=%d", a);
    // MYLOG(LEVEL_WARNING, "a=%d", a);
    // MYLOG(LEVEL_INFO, "a=%d", a);
    // MYLOG(LEVEL_DEBUG, "a=%d", a);
    // MYLOG(LEVEL_INFO, "str=%s", str);
    // MYLOG(LEVEL_INFO, "str=%s", str);
    // MYLOG(LEVEL_INFO) << "123";
#endif

    // backtrace_init();
    // neuronTest();
    // threadPoolTest();
    // myMenoryPoolTest();
    // myThreadPoolTest();
    // IOMultiplexingTest();
    // myJsonTest();
    // smartPointerTest();
    // myProtobufTest();

    
    // CommonTest::Instance()->test(MODULE_MEMORY_POOL);
    // CommonTest::Instance()->test(MODULE_THREAD_POOL);
    CommonTest::Instance()->testAll();

    while(1)
        sleep(100);
    return 0;

}
