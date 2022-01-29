// https://github.com/progschj/ThreadPool
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