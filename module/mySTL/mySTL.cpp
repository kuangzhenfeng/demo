#include "mySTL.h"
#include "mySTLPrint.h"

static void vectorTest()
{
    std::vector<int> vec;
    // vec.reserve(10);    // 预留空间
    vec.push_back(1);
    vec.emplace_back(2);
    STL_PRINT(vec);
    vec.pop_back();
    STL_PRINT(vec);
    vec = {1, 2, 3, 1, 2, 3};
    vec.erase(++vec.begin());   // 不改变vec.capacity()大小
    STL_PRINT(vec);
    vec = {1, 2, 3, 1, 2, 3};
    std::vector<int>().swap(vec);    // 清空vec，vec.capacity()清零
    STL_PRINT(vec);
}

static void dequeTest()
{
    std::deque<int> deque;
    deque.push_front(1);
    deque.push_back(2);
    STL_PRINT(deque);
    deque.pop_front();
    deque.pop_back();
    STL_PRINT(deque);
    deque = {1, 2, 3, 1, 2, 3};
    deque.erase(++deque.begin());
    STL_PRINT(deque);
}

static void listTest()
{
    std::list<int> list;
    list.push_front(1);
    list.push_back(2);
    STL_PRINT(list);
    list.pop_front();
    list.pop_back();
    STL_PRINT(list);
    list = {1, 2, 3, 1, 2, 3};
    list.remove(1);
    STL_PRINT(list);
    list = {1, 2, 3, 1, 2, 3};
    list.erase(++list.begin());
    STL_PRINT(list);
}

static void queueTest()
{
    std::queue<int> queue;
    queue.push(1);
    queue.push(2);
    STL_PRINT(queue);
    std::cout << "queue.front()=" << queue.front() << std::endl;
    std::cout << "queue.back()=" << queue.back() << std::endl;
    queue.pop();
    STL_PRINT(queue);
}

static void stackTest()
{
    std::stack<int> stack;
    stack.push(1);
    stack.push(2);
    STL_PRINT(stack);
    std::cout << "stack.top()=" << stack.top() << std::endl;
    stack.pop();
    STL_PRINT(stack);
}

static void mapTest()
{
    std::map<int, std::string> map;
    map.insert(std::make_pair(1, "a"));
    map.insert(std::make_pair(2, "b"));
    STL_PRINT(map);
    map[1] = "aa";
    map[2] = "bb";
    STL_PRINT(map);
    map.erase(1);
    STL_PRINT(map);
    map.erase(map.begin());
    STL_PRINT(map);
}

static void setTest()
{
    std::set<int> set;
    set.insert(1);
    set.insert(2);
    STL_PRINT(set);
    set.erase(1);
    STL_PRINT(set);
    set.erase(set.begin());
    STL_PRINT(set);
}

int MySTLTest::test()
{
    vectorTest();
    dequeTest();
    listTest();
    queueTest();
    stackTest();
    mapTest();
    setTest();
    return 0;
}