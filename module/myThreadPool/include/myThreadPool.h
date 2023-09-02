#ifndef __MY_THREAD_POOL_H__
#define __MY_THREAD_POOL_H__

#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <memory>
#include <thread>
#include <pthread.h>
#include "common.h"

class MyThreadPoolTest : public ModuleBase
{
public:
    MyThreadPoolTest() : ModuleBase(MODULE_THREAD_POOL, "MODULE_THREAD_POOL"){};
    int test();

private:

};

// typedef void(*TaskFun)();

// typedef enum taskState_e
// {
//     TASK_STATE_IDLE,
//     TASK_STATE_RUNNING,
// } TaskState_E;

// typedef struct threadTask_e
// {
//     int id;
//     TaskState_E taskState;
//     TaskFun taskFun;
// } ThreadTask_S;

// class MyThreadPool
// {
// public:
//     MyThreadPool();
//     ~MyThreadPool();
//     static MyThreadPool *Instance();
//     int Init(int threadNum = 20);
//     int AddTask(TaskFun taskFun);

// private:
//     int m_s32ThreadNum;
//     std::queue<TaskFun> m_taskFunQueue; // 存储任务函数的队列
//     std::vector<ThreadTask_S> m_tasks;  // 存储任务线程信息
//     std::mutex m_taskFunQueueMtx;       // m_taskFunQueue互斥锁
//     std::mutex m_tasksMtx;              // m_tasksMtx互斥锁

//     static void *ThreadPoolProcessThread(void *ptr);
//     static void *TaskThread(void *ptr);


// };



namespace my_thread_pool
{
    typedef std::function<void()> TaskFun;
    class MyThreadPool
    {
    public:
        static MyThreadPool *Instance() { static MyThreadPool s_obj; return &s_obj; }
        int create(int num)
        {
            m_bStop = false;
            // pthread_mutex_init(&m_mutex, NULL);
            // pthread_cond_init(&m_cond, NULL);
            m_workers.reserve(num);
            for(int i = 0; i < num; ++i)
            {
                m_workers.emplace_back(         // 也可以push_back(std::thread([]{}))
                    [this]
                    {
                        while(1)
                        {
                            std::unique_lock<std::mutex> lock(this->m_mutex, std::defer_lock);
                            lock.lock();
                            while(this->m_tasks.empty())
                            {
                                if(this->m_bStop)
                                    break;
                                this->m_condition.wait(lock);
                            }
                            if(this->m_bStop)
                            {
                                lock.unlock();
                                return;
                            }
                                
                            TaskFun task = std::move(this->m_tasks.front());
                            m_tasks.pop();
                            lock.unlock();
                            task();
                        }
                    }
                );
            }
            return 0;
        }
        int destory() 
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_bStop = true;
            m_condition.notify_all();
            for(auto &item : m_workers)
            {
                item.join();
            }
            return 0;
        }
        int addTask(TaskFun task)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_tasks.push(std::move(task));
            m_condition.notify_one();
            return 0;
        }
    private:
        MyThreadPool(){}
        ~MyThreadPool(){}
        bool m_bStop;
        std::queue<TaskFun> m_tasks;
        std::vector<std::thread> m_workers;
        // pthread_mutex_t m_mutex;
        // pthread_cond_t m_cond;
        std::mutex m_mutex;
        std::condition_variable m_condition;
    };
}

#endif