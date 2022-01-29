//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_set>
#include <string.h>
#include "common.h"
#include "commonTest.h"
#include "myLog.h"

namespace classTest
{
    
    class A
    {
    public:
    #if 1
        virtual void test()
    #else
        void test()
    #endif
        {
            printf("A\n");
        }
    };

    class B: public A
    {
    public:
        B(int num, std::string str) : m_num(num), m_str(str){}
        B() : m_num(0), m_str(""){}
        typedef int typeInt;
        void test()
        {
            std::cout << "B:" << m_num << m_str << std::endl; 
        }
    private:
        int m_num;
        std::string m_str;
    };

    void test_classTest()
    {
        B b;
        A &a1 = b;
        A *a2 = &b;
        b.test();
        a1.test();
        a2->test();

        B::typeInt s32Value;
    }
}

namespace vectorTest
{
    class A
    {

    };
    typedef int typeInt;
    void test_vectorTest(A a)
    {
        std::cout << "000" << std::endl;
    }
    void test_vectorTest()
    {
        std::cout << "001" << std::endl;
        int t[5] = {1,2,3,4,5};
        std::vector<int, std::allocator<int>> vec(t, t + 5);
        std::vector<int>::iterator ite1;
        for(ite1 = vec.begin(); ite1 != vec.end(); ++ite1)
        {
            std::cout << *ite1 << std::endl;
        }
        for(int i : vec)
        {
            std::cout << i << std::endl;
        }
        for(int &i : vec)
        {
            std::cout << i << std::endl;
        }

        typedef std::_Vector_base<int, std::allocator<int>>			_Base;
        typedef typename _Base::pointer			                    pointer;
        typedef __gnu_cxx::__normal_iterator<pointer, std::vector<int, std::allocator<int>>> iterator;
        iterator ite2;
        
        __gnu_cxx::__normal_iterator<std::_Vector_base<int, std::allocator<int>>::pointer, std::vector<int, std::allocator<int>>> ite3;

        int key = 3;
        find(vec.begin(), vec.end(), 3);
        sort(vec.begin(), vec.end());
    }
}
#include "../../../main/backtrace_dump.h"

#include <vector>
#include <memory>
#include <bitset>

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

int main()
{
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);


    std::vector<int> *pvec = new std::vector<int>;
    pvec->push_back(1);
    pvec->push_back(2);
    pvec->push_back(3);

    while(1) sleep(1);

#if 0
    std::shared_ptr<int> aaa;
    std::vector<int> bbb;
    std::vector<std::shared_ptr<int>> ccc;
    std::vector<std::shared_ptr<classTest::A>> ddd;
    aaa = std::make_shared<int>();
    aaa.get();
    bbb.push_back(1);
    ccc.push_back(std::make_shared<int>());
    ccc[0].get();
    ddd.push_back(std::make_shared<classTest::B>(111, "aaa"));
    ddd.push_back(std::make_shared<classTest::B>());
    ddd.push_back(std::make_shared<classTest::B>(333, "ccc"));
    ddd[0].get()->test();
    for(auto elem : ddd)
    {
        elem.get()->test();
    }

    bbb.clear();
    // bbb.swap(std::vector<int>());
    ddd.clear();
    // ddd.swap(std::vector<std::shared_ptr<classTest::A>>());

    print(111, "aaa", std::bitset<16>(377));


    

    int a = 1;
    char str[] = "abc123";
    mylog::LogManager::Instance()->setDisplayLevel(LEVEL_ALL ^ LEVEL_DEBUG ^ LEVEL_INFO);
    MYLOG(LEVEL_FATAL, "a=%d", a);
    MYLOG(LEVEL_ERROR, "a=%d", a);
    MYLOG(LEVEL_WARNING, "a=%d", a);
    MYLOG(LEVEL_INFO, "a=%d", a);
    MYLOG(LEVEL_DEBUG, "a=%d", a);
    MYLOG(LEVEL_INFO, "str=%s", str);
    MYLOG(LEVEL_INFO, "str=%s", str);

    // MYLOG(LEVEL_INFO) << "123";
    
    
    while (1)
    {
        sleep(1);
    }
    // double R = 0.349307;
    // double G = 0.317491;
    // double B = 0.333202;
    // double AVE = 0.33333;
    // std::cout << sqrt(pow(R - AVE, 2) + pow(G - AVE, 2) + pow(B - AVE, 2)) << std::endl;
    // // std::cout << sqrt(pow(R, 2) + pow(G, 2) + pow(B, 2)) << std::endl;
    // std::cout << pow(R, 2) + pow(G, 2) + pow(B, 2) << std::endl;
    // std::cout << pow(1, 2) + pow(G, 2) + pow(B, 2) << std::endl;
    // std::cout << sqrt(pow(0.1 - R, 2) + pow(0 - G, 2) + pow(0.9 - B, 2)) << std::endl;
    // std::cout << sqrt(pow(0.1 - R, 2) + pow(0 - G, 2) + pow(0.9 - B, 2)) << std::endl;
    // std::cout << sqrt(pow(1- R, 2) + pow(0 - G, 2) + pow(0 - B, 2)) << std::endl;


    // backtrace_init();
    // neuronTest();
    // threadPoolTest();
    // myMenoryPoolTest();
    // myThreadPoolTest();
    // IOMultiplexingTest();
    // myJsonTest();
    // smartPointerTest();
    myProtobufTest();

    return 0;
    
    // classTest::test_classTest();

    vectorTest::typeInt a1;
    vectorTest::A a2;
    // test_vectorTest();              // 错误
    // test_vectorTest(a1);            // 错误
    test_vectorTest(a2);            // 正确
    vectorTest::test_vectorTest();  // 正确

    std::cout << 111 << 222 << 333 << std::endl;

    std::vector<int> *vec = new std::vector<int>;

    std::unordered_multiset<std::string, std::hash<std::string>> unoSet;


#endif

    return 0;
}
