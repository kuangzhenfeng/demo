#include "mySocket.h"

int socket_main();

int MySocketTest::test()
{
    socket_main();
    exit(0);
    return 0;
    // my_coroutine::MyCoroutine coroutine;
    // coroutine.start();
    // MYLOG(LEVEL_DEBUG, "aaa");
    // sleep(1);
    // coroutine.start();
    // MYLOG(LEVEL_DEBUG, "bbb");
    // sleep(1);
    // coroutine.start();
    // MYLOG(LEVEL_DEBUG, "ccc");
    // sleep(1);
    // coroutine.start();
    // MYLOG(LEVEL_DEBUG, "ddd");
    // sleep(1);
    // coroutine.start();
    // MYLOG(LEVEL_DEBUG, "eee");
    // sleep(1);
    // coroutine.start();
    // MYLOG(LEVEL_DEBUG, "fff");
    // sleep(1);
    // coroutine.start();
    // MYLOG(LEVEL_DEBUG, "ggg");
    // sleep(1);
    while(1)
        sleep(1);
    return 0;
}




int socket_main()
{
    my_reactor::MainReactor::Instance()->start();
    my_reactor::SubReactor::Instance()->start();
    while(1)
        sleep(1);
    return 0;
}

namespace my_reactor
{
    /* accept也属于读IO操作的回调 */
    int MainReactor::accept_cb(int fd, int events, void *arg)
    {
        struct sockitem *si = (struct sockitem *)arg;
        struct epoll_event ev;

        struct sockaddr_in client;
        memset(&client, 0, sizeof(struct sockaddr_in));
        socklen_t caddr_len = sizeof(struct sockaddr_in);

        int clientfd = accept(si->sockfd, (struct sockaddr*)&client, &caddr_len);
        if(clientfd < 0)
        {
            printf("# accept error\n");
            return clientfd;
        }

        char str[INET_ADDRSTRLEN] = {0};
        printf("recv from %s at port %d\n", inet_ntop(AF_INET, &client.sin_addr, str, sizeof(str)),
            ntohs(client.sin_port));

    #if 1
        SubReactor::Instance()->addTask(clientfd);
    #else
        struct sockitem *client_si = (struct sockitem*)malloc(sizeof(struct sockitem));
        client_si->sockfd = clientfd;
        client_si->callback = recv_cb;  // accept完的下一步就是接收客户端数据
        client_si->epfd = si->epfd;

        memset(&ev, 0, sizeof(struct epoll_event));
        ev.events = EPOLLIN;
        ev.data.ptr = client_si;
        epoll_ctl(si->epfd, EPOLL_CTL_ADD, clientfd, &ev);  // 把客户端socket增加到epoll中监听
    #endif
        return clientfd;
    }

    void MainReactor::HandleProcessThread(void *para)
    {
        MainReactor *mainReactor = (MainReactor *)para;
        const int port = 1234;

        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
        {
            DEBUG_PERROR("socket() error");
            return;
        }

        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(struct sockaddr_in));

        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(port);

        int is_reuse_address = 1;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&is_reuse_address, sizeof(int));   // 端口复用

        if(bind(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) < 0)
        {
            DEBUG_PERROR("bind() error");
            return;
        }

        if(listen(sockfd, 5) < 0)
        {
            DEBUG_PERROR("listen() error");
            return;
        }

        /* go epoll */
        struct reactor ra;
        ra.epfd = epoll_create(1);

        struct sockitem *si = (struct sockitem*)malloc(sizeof(struct sockitem));    // 自定义数据，用于传递给回调函数
        si->sockfd = sockfd;
        si->callback = accept_cb;
        si->epfd = ra.epfd; // sockitem 中增加一个epfd成员以便回调函数中使用

        struct epoll_event ev;
        memset(&ev, 0, sizeof(struct epoll_event));
        ev.events = EPOLLIN;    // 默认LT
        ev.data.ptr = si;

        epoll_ctl(ra.epfd, EPOLL_CTL_ADD, sockfd, &ev);    // 添加到事件到epoll
        while(mainReactor->m_bRun)
        {
            int nready = epoll_wait(ra.epfd, ra.events, MAX_EVENTS_NUM, -1);
            if(nready < 0)
            {
                DEBUG_PERROR("epoll_wait() error");
                break;
            }

            for(int i = 0; i < nready; ++i)
            {
                si = (struct sockitem *)ra.events[i].data.ptr;
                if(ra.events[i].events & (EPOLLIN | EPOLLOUT))
                {
                    if(si->callback != NULL)
                        si->callback(si->sockfd, ra.events[i].events, si);  // 调用回调函数
                }
            
            }
        }
    }

    void SubReactor::addTask(int clientFd)
    {
        std::lock_guard<std::mutex> lock(m_queueMutex);
        m_tasks.push([clientFd]{std::make_shared<MyCoroutine>()->start(clientFd);});
        unsigned long long val = 1;
        write(m_evfd, &val, sizeof(unsigned long long));    // 唤醒epoll
    }

    void SubReactor::processTask()
    {
        std::lock_guard<std::mutex> lock(m_queueMutex);
        while(!m_tasks.empty())
        {
            auto task = m_tasks.front();
            task();
            m_tasks.pop();   
        }
    }

    void SubReactor::async_recv(struct sockitem *si)
    {
        MYLOG(LEVEL_INFO, "OK");
        si->epfd = m_ra.epfd;

        struct epoll_event ev;
        memset(&ev, 0, sizeof(struct epoll_event));
        ev.events = EPOLLIN;    // 默认LT
        ev.data.ptr = si;

        epoll_ctl(m_ra.epfd, EPOLL_CTL_ADD, si->sockfd, &ev);    // 添加到事件到epoll
    }

    void SubReactor::async_send(struct sockitem *si)
    {
        MYLOG(LEVEL_INFO, "OK");
        si->epfd = m_ra.epfd;

        struct epoll_event ev;
        memset(&ev, 0, sizeof(struct epoll_event));
        ev.events = EPOLLOUT | EPOLLET; // 写的时候最好还是用ET
        ev.data.ptr = si;

        epoll_ctl(m_ra.epfd, EPOLL_CTL_MOD, si->sockfd, &ev);    // 添加到事件到epoll
    }

    void SubReactor::close(int clientfd)
    {
        ::close(clientfd);
        /* 将当前客户端socket从epoll中删除 */
        struct epoll_event ev;
        epoll_ctl(m_ra.epfd, EPOLL_CTL_DEL, clientfd, &ev);
    }
    
    void SubReactor::HandleProcessThread(void *para)
    {
        SubReactor *subReactor = (SubReactor *)para;
        subReactor->m_evfd = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK);
        /* go epoll */
        struct reactor &ra = subReactor->m_ra;
        ra.epfd = epoll_create(1);

        struct epoll_event ev;
        memset(&ev, 0, sizeof(struct epoll_event));
        ev.events = EPOLLIN;    // 默认LT
        // ev.data.fd = subReactor->m_evfd;
        epoll_ctl(subReactor->m_ra.epfd, EPOLL_CTL_ADD, subReactor->m_evfd, &ev);    // 添加到事件到epoll
        
        while(subReactor->m_bRun)
        {
            int nready = epoll_wait(ra.epfd, ra.events, MAX_EVENTS_NUM, -1);
            if(nready < 0)
            {
                DEBUG_PERROR("epoll_wait() error");
                break;
            }

            for(int i = 0; i < nready; ++i)
            {
                struct sockitem *si = (struct sockitem *)ra.events[i].data.ptr;
                if(ra.events[i].events & (EPOLLIN | EPOLLOUT))
                {
                    if(si != NULL && si->callback != NULL)
                        si->callback(si->sockfd, ra.events[i].events, si);  // 调用回调函数
                }
            }
            subReactor->processTask();
        }
    }
#if 1
    int MyCoroutine::recv_cb(int fd, int events, void *arg)
    {
        struct sockitem *si = (struct sockitem *)arg;
        struct epoll_event ev;

        int clientfd = si->sockfd;
        si->recvlength = recv(clientfd, si->recvbuffer, my_reactor::MAX_BUFFER_SIZE, 0);
        if(si->recvlength <= 0)
        {
            if(si->recvlength < 0)
            {
                if(errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)
                {   // 被打断直接返回的情况
                    return si->recvlength;
                }
            }
            else
            {
                printf("# client disconnected...\n");
            }
            
            /* 将当前客户端socket从epoll中删除 */
            close(clientfd);
            ev.events = EPOLLIN;
            ev.data.ptr = si;
            epoll_ctl(si->epfd, EPOLL_CTL_DEL, clientfd, &ev);  
            free(si);
        }
        else
        {
            printf("# recv data from fd:%d : %s , len = %d\n", clientfd, si->recvbuffer, si->recvlength);
            /* 此处进行数据处理，比如解析接收到的HTTP报文等等 */
            /*** ..... ***/

            // si->callback = send_cb;     // 回调函数要切换成写回调
            // struct epoll_event ev;
            // ev.events = EPOLLOUT | EPOLLET; // 写的时候最好还是用ET
            // ev.data.ptr = si;
            // epoll_ctl(si->epfd, EPOLL_CTL_MOD, si->sockfd, &ev);
        }
        resume(clientfd);

        return si->recvlength;
    }
    /* 写IO回调函数 */
    int MyCoroutine::send_cb(int fd, int events, void *arg)
    {
        struct sockitem *si = (struct sockitem *)arg;
        struct epoll_event ev;

        int clientfd = si->sockfd;
        
        /* 写回的数据此处先简单处理 */
        const char* hello = "Hello!\n";
        si->sendlength = send(clientfd, si->sendbuffer, strlen(si->sendbuffer), 0);

        si->callback = std::bind(&MyCoroutine::recv_cb, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3); // 切回读的回调
        ev.events = EPOLLIN;
        ev.data.ptr = si;
        epoll_ctl(si->epfd, EPOLL_CTL_MOD, si->sockfd, &ev);

        resume(clientfd);
        return si->sendlength;
    }
#else
    /* 读IO回调函数 */
    int MyCoroutine::recv_cb(int fd, int events, void *arg)
    {
        struct sockitem *si = (struct sockitem *)arg;
        struct epoll_event ev;

        int clientfd = si->sockfd;
        char buffer[1024] = {0};
        int ret = recv(clientfd, buffer, 1024, 0);
        if(ret <= 0)
        {
            if(ret < 0)
            {
                if(errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)
                {   // 被打断直接返回的情况
                    return ret;
                }
            }
            else
            {
                printf("# client disconnected...\n");
            }
            
            /* 将当前客户端socket从epoll中删除 */
            close(clientfd);
            ev.events = EPOLLIN;
            ev.data.ptr = si;
            epoll_ctl(si->epfd, EPOLL_CTL_DEL, clientfd, &ev);  
            free(si);
        }
        else
        {
            printf("# recv data from fd:%d : %s , len = %d\n", clientfd, buffer, ret);
            /* 此处进行数据处理，比如解析接收到的HTTP报文等等 */
            /*** ..... ***/

            si->callback = std::bind(&MyCoroutine::send_cb, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);     // 回调函数要切换成写回调
            struct epoll_event ev;
            ev.events = EPOLLOUT | EPOLLET; // 写的时候最好还是用ET
            ev.data.ptr = si;
            epoll_ctl(si->epfd, EPOLL_CTL_MOD, si->sockfd, &ev);
        }

        return ret;
    }
    
    /* 写IO回调函数 */
    int MyCoroutine::send_cb(int fd, int events, void *arg)
    {
        struct sockitem *si = (struct sockitem *)arg;
        struct epoll_event ev;

        int clientfd = si->sockfd;
        
        /* 写回的数据此处先简单处理 */
        const char* hello = "Hello!\n";
        int ret = send(clientfd, hello, strlen(hello), 0);

        si->callback = std::bind(&MyCoroutine::recv_cb, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3); // 切回读的回调
        ev.events = EPOLLIN;
        ev.data.ptr = si;
        epoll_ctl(si->epfd, EPOLL_CTL_MOD, si->sockfd, &ev);

        return ret;
    }
#endif

}


