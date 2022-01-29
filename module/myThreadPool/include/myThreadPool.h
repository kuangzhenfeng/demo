#ifndef __MY_THREAD_POOL_H__
#define __MY_THREAD_POOL_H__

#include <queue>
#include <vector>
#include <mutex>
#include <pthread.h>

typedef void(*TaskFun)();

typedef enum taskState_e
{
    TASK_STATE_IDLE,
    TASK_STATE_RUNNING,
} TaskState_E;

typedef struct threadTask_e
{
    int id;
    TaskState_E taskState;
    TaskFun taskFun;
} ThreadTask_S;

class MyThreadPool
{
public:
    MyThreadPool();
    ~MyThreadPool();
    static MyThreadPool *Instance();
    int Init(int threadNum = 20);
    int AddTask(TaskFun taskFun);

private:
    int m_s32ThreadNum;
    std::queue<TaskFun> m_taskFunQueue; // 存储任务函数的队列
    std::vector<ThreadTask_S> m_tasks;  // 存储任务线程信息
    std::mutex m_taskFunQueueMtx;       // m_taskFunQueue互斥锁
    std::mutex m_tasksMtx;              // m_tasksMtx互斥锁

    static void *ThreadPoolProcessThread(void *ptr);
    static void *TaskThread(void *ptr);


};




#endif