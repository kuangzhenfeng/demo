#include "IOMultiplexing.h"
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include "common.h"

int selectTest()
{
    DEBUG("OK");
    char buf[1024] = {0};
    int bufLen = 0;
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    // FD_SET(STDOUT_FILENO, &fds);
    // FD_SET(STDERR_FILENO, &fds);
    while(1)
    {
        memset(buf, 0, sizeof(buf));
        DEBUG("[enter]");
        select(FD_SETSIZE, &fds, NULL, NULL, NULL);
        DEBUG("[exit]");
        bufLen = recv(STDIN_FILENO, buf, sizeof(buf), 0);
        // bufLen = read(STDIN_FILENO, buf, sizeof(buf));
        DEBUG("[out][%d]%s\e[0m", bufLen, buf);
        sleep(1);
    }
    return 0;
}

int epollTest()
{
    DEBUG("OK");
    const int MAX_OPEN_FD = 1024;
    int epollFd;
    int eventCount = 0;
    char buf[1024] = {0};
    int bufLen = 0;
    epollFd = epoll_create(MAX_OPEN_FD);
    if (epollFd == -1)
    {
        DEBUG_PERROR("epoll_create error");
        return -1;
    }
    epoll_event event = {0};
    epoll_event eventList[MAX_OPEN_FD] = {0};
    event.events = EPOLLIN;
    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, STDIN_FILENO, &event) == -1)
    {
        DEBUG_PERROR("epoll_ctl error");
        return -1;
    }
    // if (epoll_ctl(epollFd, EPOLL_CTL_ADD, STDOUT_FILENO, &event) == -1)
    // {
    //     DEBUG("epoll_ctl error");
    //     return -1;
    // }
    // if (epoll_ctl(epollFd, EPOLL_CTL_ADD, STDERR_FILENO, &event) == -1)
    // {
    //     DEBUG("epoll_ctl error");
    //     return -1;
    // }
    
    while(1)
    {
        DEBUG("[enter]");
        eventCount = epoll_wait(epollFd, eventList, MAX_OPEN_FD, -1);
        DEBUG("[exit]");
        for (int i = 0 ; i < eventCount; i++)
        {
            // int events = eventList[i].events;
            // bufLen = recv(eventList[i].data.fd, buf, sizeof(buf), 0);
            bufLen = read(eventList[i].data.fd, buf, sizeof(buf));
            DEBUG("[out][%d]%s\e[0m\n", bufLen, buf);
        }
        
        sleep(1);
    }

    return 0;
}