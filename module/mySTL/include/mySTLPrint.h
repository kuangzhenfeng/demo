#ifndef __MY_STL_PRINT_H__
#define __MY_STL_PRINT_H__

#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define STL_PRINT(obj)          \
    do                          \
    {                           \
        MYLOG(LEVEL_DEBUG, ""); \
        _STLPrint(obj);         \
    } while (0)

template<class T>
static void _STLPrint(T &obj)
{
    for(auto &item : obj)
    {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

template<typename T>
static void _STLPrint(std::queue<T> obj)
{
    while(!obj.empty())
    {
        std::cout << obj.front() << " ";
        obj.pop();
    }
    std::cout << std::endl;
}

template<typename T>
static void _STLPrint(std::stack<T> obj)
{
    while(!obj.empty())
    {
        std::cout << obj.top() << " ";
        obj.pop();
    }
    std::cout << std::endl;
}

template<typename _Key, typename _Tp>
static void _STLPrint(std::map<_Key, _Tp> obj)
{
    for(auto &item : obj)
    {
        std::cout << "[" << item.first << "]=" << item.second << std::endl;
    }
}

#endif
