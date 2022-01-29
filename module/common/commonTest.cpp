#include "commonTest.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include "common.h"
#include "neuron.h"
#include "threadPool.h"
#include "myMemoryPool.h"
#include "myThreadPool.h"
#include "IOMultiplexing.h"
#include "myJson.h"
#include "smartPointer.h"
#include "myProtobuf.h"

int neuronTest()
{
    printf("neuronTest start\n");
    std::vector<int> input1 = {3, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> input2 = {2, 4, 5, 6, 7, 8, 9, 10, 1, 2};
    std::vector<int> output;
    for(int i = 0; i < 10; ++i)
    {
        output.push_back(input1[i] * input2[i]);
    }
    Neuron neu(2);
    for(int i = 0; i < 1; ++i)
    {
        neu.train(input1, input2, output);
    }
    for(int i = 0; i < 10; ++i)
    {
        printf("%d * %d = %d\n",input1[i], input2[i], neu.test(input1[i], input2[i]));
    }
    printf("neuronTest end\n");
    return 0;
}


int threadPoolTest()
{
    // create thread pool with 4 worker threads
    ThreadPool pool(4);

    // enqueue and store future
    auto result = pool.enqueue([](int answer) { return answer; }, 42);

    // get result from future
    std::cout << result.get() << std::endl;
    return 0;
}

int myMenoryPoolTest()
{
    MyMemoryPool *pMyMemoryPool = MyMemoryPool::Instance();
    for(int i = 0; i < 200; ++i)
    {
        pMyMemoryPool->allocate(64);
    }
    return 0;
}

static void myThreadPoolTestTask()
{
    static int taskNum = 0;
    ++taskNum;
    int num = taskNum;
    DEBUG("%d task start", num);
    sleep(1);
    char *p = (char *)malloc(4);
    p += 6;
    *p = 1;
    printf("*p1=%d\n", *p);
    p += 1;
    printf("*p2=%d\n", *p);
    DEBUG("%d task end", num);
}

int myThreadPoolTest()
{
    MyThreadPool *pMyThreadPool = MyThreadPool::Instance();
    pMyThreadPool->Init(3);
    for(int i = 0; i < 10; ++i)
    {
        pMyThreadPool->AddTask(myThreadPoolTestTask);
    }

    while(1)
    {
        sleep(1);
    }
    return 0;
}

int IOMultiplexingTest()
{
    selectTest();
    epollTest();
    return 0;
}

int myJsonTest()
{
    // MyJson::test();
    MyJson myJson;
    myJson.Parse("{\"project\":\"rapidjson_org\",\"stars\":11}");
    DEBUG("%s", myJson.toString().c_str());
    myJson.parse("{\"project\":\"rapidjson_new\",\"stars\":22}");
    DEBUG("%s", myJson.toString().c_str());
    return 0;
}

int smartPointerTest()
{
    SmartPointer::test();
    return 0;
}

int myProtobufTest()
{
    MyProtobuf::test();
    return 0;
}
