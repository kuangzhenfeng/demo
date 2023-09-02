// https://github.com/progschj/ThreadPool
#include "myThreadPoolThird.h"
#if 0
#include <iostream>
#include "threadPool.h"

int judge(int dE, int t)
{
    if(dE < 0)
    {
        return 1;
    }   
    float d = exp(-(dE / t));
    if(d > rand())  // rand()表示0到1的随机数
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int threadPool_test()
{
    // create thread pool with 4 worker threads
    ThreadPool pool(4);

    // enqueue and store future
    auto result = pool.enqueue([](int answer) { return answer; }, 42);

    // get result from future
    std::cout << result.get() << std::endl;
    return 0;
}

#endif

int MyThreadPoolThirdTest::test()
{
    std::cout << "000" << std::endl;
    // create thread pool with 4 worker threads
    ThreadPool pool(4);
    std::cout << "111" << std::endl;

    // enqueue and store future
    auto result = pool.enqueue([](int answer) { return answer; }, 42);
    std::cout << "222" << std::endl;

    // get result from future
    std::cout << result.get() << std::endl;
    return 0;    
}