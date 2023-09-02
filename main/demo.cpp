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
    using namespace std;
    vector<string> q;
{
    string a = "10";
    string b = "20";
    string c = "30";
    string d = "40";
    {
        TimeConsum t;
        for (int i = 0; i < 29; ++i)
        {
            a += a;
            b += b;
            c += c;
            d += d;
            static int count = 0;
            cout << "count=" <<  ++count << " size=" << a.size() << endl;
        }
    }
   
    cout << &a << " " << a[0] << endl;
    cout << &b << " " << b[0] << endl;
    cout << &c << " " << c[0] << endl;
    cout << &d << " " << d[0] << endl;
    {
        TimeConsum t;
        // for (int i = 0; i < 10000 * 1000; ++i)
        {
            // string a = "10";
            q.push_back(a);
        }
    }
    {
        TimeConsum t;
        // for (int i = 0; i < 10000 * 1000; ++i)
        {
            // string b = "10";
            q.push_back(std::move(b));
        }
    }
    {
        TimeConsum t;
        // for (int i = 0; i < 10000 * 1000; ++i)
        {
            // string c = "10";
            q.emplace_back(c);
        }
    }
    {
        TimeConsum t;
        // for (int i = 0; i < 10000 * 1000; ++i)
        {
            // string d = "10";
            q.emplace_back(std::move(d));
        }
    }
    
    
    
    
    cout << &a << " " << a[0] << endl;
    cout << &b << " " << b[0] << endl;
    cout << &c << " " << c[0] << endl;
    cout << &d << " " << d[0] << endl;
}
    cout << &q[0] << " " << q[0][0] << endl;
    cout << &q[1] << " " << q[1][0] << endl;
    cout << &q[2] << " " << q[2][0] << endl;
    cout << &q[3] << " " << q[3][0] << endl;
    
    

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
