#include "myThreadPool.h"
#include <unistd.h>

MyThreadPool::MyThreadPool()
{
    m_s32ThreadNum = 0;
}

MyThreadPool::~MyThreadPool()
{

}

MyThreadPool *MyThreadPool::Instance()
{
    static MyThreadPool instance;
    return &instance;
}

int MyThreadPool::Init(int threadNum)
{
    std::lock_guard<std::mutex> lock(m_tasksMtx);
    pthread_t tid;
    pthread_create(&tid, NULL, ThreadPoolProcessThread, NULL);
    m_s32ThreadNum = threadNum;
    for(int i = 0; i < threadNum; ++i)
    {
        ThreadTask_S task;
        task.id = i;
        task.taskFun = NULL;
        task.taskState = TASK_STATE_IDLE;
        m_tasks.push_back(task);
        pthread_create(&tid, NULL, TaskThread, &m_tasks[i].id);
    }
    return 0;
}

void *MyThreadPool::ThreadPoolProcessThread(void *ptr)
{
    MyThreadPool *pMyThreadPool = MyThreadPool::Instance();
    while(1)
    {
        pMyThreadPool->m_taskFunQueueMtx.lock();
        pMyThreadPool->m_tasksMtx.lock();
        if(!pMyThreadPool->m_taskFunQueue.empty())
        {
            for(auto &task : pMyThreadPool->m_tasks)
            {
                if(task.taskState == TASK_STATE_IDLE)
                {
                    TaskFun taskFun = pMyThreadPool->m_taskFunQueue.front();
                    pMyThreadPool->m_taskFunQueue.pop();
                    task.taskFun = taskFun;
                    task.taskState = TASK_STATE_RUNNING;
                    break;
                }
            }
        }
        pMyThreadPool-> m_taskFunQueueMtx.unlock();
        pMyThreadPool-> m_tasksMtx.unlock();
        usleep(10 * 1000);
    }
}

void *MyThreadPool::TaskThread(void *ptr)
{
    MyThreadPool *pMyThreadPool = MyThreadPool::Instance();
    int id = *(int *)ptr;
    while(1)
    {
        pMyThreadPool->m_tasksMtx.lock();
        if(pMyThreadPool->m_tasks[id].taskState == TASK_STATE_IDLE)
        {
            pMyThreadPool->m_tasksMtx.unlock();
            usleep(10 * 1000);
            continue;
        }
        pMyThreadPool->m_tasksMtx.unlock();
        pMyThreadPool->m_tasks[id].taskFun();
        pMyThreadPool->m_tasksMtx.lock();
        pMyThreadPool->m_tasks[id].taskState = TASK_STATE_IDLE;
        pMyThreadPool->m_tasksMtx.unlock();
        usleep(10 * 1000);
    }
}

int MyThreadPool::AddTask(TaskFun taskFun)
{
    std::lock_guard<std::mutex> lock(m_taskFunQueueMtx);
    m_taskFunQueue.push(taskFun);
    return 0;
}

static void myThreadPoolTestTask()
{
    static int taskNum = 0;
    ++taskNum;
    int num = taskNum;
    DEBUG("%d task start", num);
    sleep(1);
    char *p = (char *)malloc(8);
    char *pt = p;
    pt += 6;
    *pt = 1;
    printf("*p1=%d\n", *pt);
    pt += 1;
    printf("*p2=%d\n", *pt);
    free(p);
    DEBUG("%d task end", num);
}

int MyThreadPoolTest::test()
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
