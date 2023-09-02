#include "myIPC.h"

#include "myThreadPoolThird.h"
#include <set>

int MyIPCTest::test()
{
    my_shared_memory::SharedMemory sharedMemory;
    my_shared_memory::ProcessFork processFork;
    if(processFork.getPid() > 0)
    {
        // 父进程，写端
        std::cout << "father" << std::endl;
        // sleep(2);
        ThreadPool pool(8);
        for(int i = 0; i < 1000; ++i)
        {
            auto result = pool.enqueue([&, i]() { sharedMemory.write(my_shared_memory::SHM_MODULE_COMMON, const_cast<char *>(std::to_string(i).c_str()), 4);});
        }
        // while(1)
        // {
        //     auto result = pool.enqueue([&]() { static int num = 100; if(num > 180) return; sharedMemory.write(my_shared_memory::SHM_MODULE_COMMON, const_cast<char *>(std::to_string(num++).c_str()), 4);});
        // }
        // std::cout << result.get() << std::endl;
        // sharedMemory.write(my_shared_memory::SHM_MODULE_COMMON, (char *)"666", 4);
    }
    else
    {
        // 子进程，读端
        std::cout << "son" << std::endl;
        // char buffer[100] = {0};
        // sleep(2);
        ThreadPool pool(8);
        std::set<int> set;
        for(int i = 0; i < 1000; ++i)
        {
            auto result = pool.enqueue([&]() { char buffer[100] = {0}; sharedMemory.read(my_shared_memory::SHM_MODULE_COMMON, buffer, 4); std::cout << buffer << std::endl; set.insert(atoi(buffer));});
        }
        while(1)
        {
            // if(set.size() >= 1000)
            {
                std::cout << "OK set.size()=" << set.size() << std::endl;
                sleep(1);
            }
        }
        // sharedMemory.read(my_shared_memory::SHM_MODULE_COMMON, buffer, 4);
        // std::cout << buffer << std::endl;

    }
    while(1)
        sleep(1);
    return 0;
}
