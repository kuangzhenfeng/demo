#ifndef __MY_IPC_H__
#define __MY_IPC_H__

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <map>
#include <tuple>
#include <cstring>
#include <semaphore.h>
#include "common.h"

// ipcs命令：查看消息队列、共享内存和信号量（仅systemV可用）
// ls /dev/shm（posix可用）

// TODO: FIFO PIPE SOCKET(AF_LOCAL)

class MyIPCTest : public ModuleBase
{
public:
    MyIPCTest() : ModuleBase(MODULE_IPC, "MODULE_IPC"){};
    int test();

private:
};

namespace my_shared_memory
{
    #define SHM_NAME "my_shm"
    #define SHM_SIZE 16 * 1024
    
    #define SEM_FULL_NAME "sem_full"
    #define SEM_EMPTY_NAME "sem_empty"


    enum ShmModule : unsigned char
    {
        SHM_MODULE_COMMON,
        SHM_MODULE_CMD,
        SHM_MODULE_DATA,

        SHM_MODULE_MAX,
    };
    typedef struct
    {
        ShmModule type;
        int size;
        // char data[0];
    } ShmCfg;
    
    class ProcessFork
    {
    public:
        ProcessFork()
        {
            m_pid = fork();
        }
        pid_t getPid()
        {
            return m_pid;
        }
    private:
        pid_t m_pid;
    };

    class SharedMemory
    {
    public:
        SharedMemory()
        {
            deinit();
            init();
        }
        void init()
        {
            const ShmCfg shmCfg[] = {
                {SHM_MODULE_COMMON, 1024}, 
                {SHM_MODULE_CMD, 512}, 
                {SHM_MODULE_DATA, 512},
            };
            m_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
            ftruncate(m_fd, SHM_SIZE);
            m_data = (char *)mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, m_fd, 0);

            m_semFull = sem_open(SEM_FULL_NAME, O_CREAT, 0600, 0);
            m_semEmpty = sem_open(SEM_EMPTY_NAME, O_CREAT, 0600, 1);

            char *addr = m_data;
            for(int i = 0; i < sizeof(shmCfg) / sizeof(ShmCfg); ++i)
            {
                m_shmModuleMap.insert(std::make_pair(shmCfg[i].type, std::make_tuple(addr, shmCfg[i].size)));
                addr += shmCfg[i].size;
            }
        }
        void deinit()
        {
            sem_close(m_semFull);
            sem_close(m_semEmpty);
            sem_unlink(SEM_FULL_NAME);
            sem_unlink(SEM_EMPTY_NAME);

            munmap(m_data, SHM_SIZE);
            shm_unlink(SHM_NAME);
        }
        ~SharedMemory()
        {
            deinit();
        }
        int read(ShmModule module, char *buffer, int size)
        {
            MYLOG(LEVEL_WARNING, "111");
            sem_wait(m_semFull);
            MYLOG(LEVEL_WARNING, "222");
            memcpy(buffer, std::get<0>(m_shmModuleMap[module]), size);
            MYLOG(LEVEL_WARNING, "333");
            sem_post(m_semEmpty);
            MYLOG(LEVEL_WARNING, "444");
            return 0;
        }
        int write(ShmModule module, char *buffer, int size)
        {
            MYLOG(LEVEL_INFO, "AAA");
            sem_wait(m_semEmpty);
            MYLOG(LEVEL_INFO, "BBB");
            memcpy(std::get<0>(m_shmModuleMap[module]), buffer, size);
            MYLOG(LEVEL_INFO, "CCC");
            sem_post(m_semFull);
            MYLOG(LEVEL_INFO, "DDD");
            return 0;
        }

    private:
        int m_fd;
        char *m_data;
        sem_t *m_semFull;
        sem_t *m_semEmpty;
        std::map<ShmModule, std::tuple<char *, int>> m_shmModuleMap;  // tuple<addr，size>
    };
}

#endif