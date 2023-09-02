#ifndef __MY_SOCKET_H__
#define __MY_SOCKET_H__


#include <sys/eventfd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <boost/asio/ip/tcp.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/make_shared.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/write.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/container/vector.hpp>
#include <boost/asio/coroutine.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/system/system_error.hpp>
#include <thread>
#include <functional>
#include <memory>
#include <queue>
#include "common.h"

class MySocketTest : public ModuleBase
{
public:
    MySocketTest() : ModuleBase(MODULE_SOCKET, "MODULE_SOCKET"){};
    int test();
};

int accept_cb(int fd, int events, void *arg);
int recv_cb(int fd, int events, void *arg);
namespace my_reactor
{

    const int MAX_BUFFER_SIZE = 1024;
    const int MAX_EVENTS_NUM = 512;
    struct sockitem
    {
        int sockfd;
        // int (*callback)(int fd, int events, void *arg);
        std::function<int(int, int, void *)> callback;
        int epfd;

        char recvbuffer[MAX_BUFFER_SIZE];   // 接收缓冲
        char sendbuffer[MAX_BUFFER_SIZE];   // 发送缓冲
        int recvlength;                     // 接收缓冲区中的数据长度
        int sendlength;                     // 发送缓冲区中的数据长度
    };
    struct reactor
    {
        int epfd;
        struct epoll_event events[MAX_EVENTS_NUM];
    };

    class MyCoroutine;

    class MainReactor
    {
    public:
        static MainReactor *Instance(){static MainReactor s_obj; return &s_obj;}
        void start()
        {
            if (!m_Thread)
            {
                m_bRun = true;
                m_Thread = std::make_shared<std::thread>(HandleProcessThread, this);
            }
        }
        void stop()
        {
            if(m_Thread)
            {
                m_bRun = false;
                m_Thread->join();
                m_Thread.reset();
            }
        }
    private:
        MainReactor(){}
        ~MainReactor(){}
        static int accept_cb(int fd, int events, void *arg);
        static void HandleProcessThread(void *para);
        bool m_bRun = false;
        std::shared_ptr<std::thread> m_Thread{};
    };

    class SubReactor
    {
    public:
        static SubReactor *Instance(){static SubReactor s_obj; return &s_obj;}
        void start()
        {
            if (!m_Thread)
            {
                m_bRun = true;
                m_Thread = std::make_shared<std::thread>(HandleProcessThread, this);
            }
        }
        void stop()
        {
            if(m_Thread)
            {
                m_bRun = false;
                m_Thread->join();
                m_Thread.reset();
            }
        }
        void addTask(int clientFd);
        void async_recv(struct sockitem *si);
        void async_send(struct sockitem *si);
        void close(int clientfd);
    private:
        SubReactor(){}
        ~SubReactor(){}
        void processTask();
        static void HandleProcessThread(void *para);
        bool m_bRun = false;
        std::shared_ptr<std::thread> m_Thread{};
        struct reactor m_ra;
        int m_evfd;
        std::queue<std::function<void()>> m_tasks;
        std::mutex m_queueMutex;
    };
    class MyCoroutine : public boost::asio::coroutine
    {
    public:
        void start(int clientfd)
        {
            // m_si = std::make_shared<struct sockitem>();
            m_si = (struct sockitem *)malloc(sizeof(struct sockitem));
            process(clientfd);
        }
        void resume(int clientfd)
        {
            process(clientfd);
        }
    private:
        int recv_cb(int fd, int events, void *arg);
        int send_cb(int fd, int events, void *arg);

#include <boost/asio/yield.hpp>
        void process(int clientfd)
        {
            reenter(this)
            {
                // yield MYLOG(LEVEL_DEBUG, "111");
                // yield MYLOG(LEVEL_DEBUG, "222");
                // yield MYLOG(LEVEL_DEBUG, "333");
                // yield MYLOG(LEVEL_DEBUG, "444");
                MYLOG(LEVEL_INFO, "111"); 
                m_si->sockfd = clientfd;
                m_si->callback = std::bind(&MyCoroutine::recv_cb, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);     // TODO: 读回调，获取buffer
                // yield SubReactor::Instance()->async_recv(m_si.get());
                yield SubReactor::Instance()->async_recv(m_si);
                MYLOG(LEVEL_INFO, "# recv data from fd:%d : %s , len = %d\n", m_si->sockfd, m_si->recvbuffer, m_si->recvlength);
                MYLOG(LEVEL_INFO, "222");\
                sprintf(m_si->sendbuffer, "HHHHH_%s", m_si->recvbuffer);
                m_si->sockfd = clientfd;
                m_si->callback = std::bind(&MyCoroutine::send_cb, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
                yield SubReactor::Instance()->async_send(m_si);
                MYLOG(LEVEL_INFO, "333");
                SubReactor::Instance()->close(clientfd);
                free(m_si);
            }
        }
#include <boost/asio/unyield.hpp>
        // std::shared_ptr<struct sockitem> m_si;
        struct sockitem* m_si;
    };
}

namespace my_socket
{
    enum class Protocol
    {
        TCP,
        UDP,
    };

    typedef struct
    {
        in_addr_t srcAddr;
        in_port_t srcPort;
        in_addr_t dstAddr;
        in_port_t dstPort;
        Protocol protocol;
    } SocketInfo;

    class SocketBase
    {
    protected:
        // SocketBase(unsigned int srcAddr, int srcPort, unsigned int  dstAddr, int dstPort, Protocol protocol) : 
        //         _srcAddr(srcAddr), _srcPort(srcAddr), _dstAddr(dstAddr), _dstPort(dstPort), _protocol(protocol){}
        void linsten()
        {
            int listenFd = socket(AF_INET, _info.protocol == Protocol::TCP ? SOCK_STREAM : SOCK_DGRAM, 0);
            struct sockaddr_in srcAddr;
            srcAddr.sin_family = AF_INET;
            srcAddr.sin_port = _info.srcPort;
            srcAddr.sin_addr.s_addr = _info.srcAddr;
            bind(listenFd, reinterpret_cast<sockaddr *>(&srcAddr), sizeof(srcAddr));
        }
        virtual int send();


        SocketInfo _info;
        int _epollFd;
    };

    class TCPServer : public SocketBase
    {
        // TCPServer(int listenPort = 8080) : _srcAddr(INADDR_ANY), _srcPort(listenPort), _protocol(Protocol::TCP){}
        TCPServer(int listenPort = 8080)
        {
            const int MAX_OPEN_FD = 1024;

            _info.srcAddr = htonl(INADDR_ANY);
            _info.srcPort = htons(listenPort);
            _info.protocol = Protocol::TCP;

            _epollFd = epoll_create(MAX_OPEN_FD);
            if (-1 == _epollFd)
            {
                DEBUG_PERROR("epoll_create error");
            }
        }

        // int async_read(std::string buf, std::function<void()> cb)
        // {

        // }
        // void start() override
        // {

        // }
        int send() override
        {
            return 0;
        }
    };

    // class TCPClient : public SocketBase
    // {
    //     TCPClient(uint32_t dstAddr, uint16_t dstPort)
    //     {
    //         _info.dstAddr = dstAddr;
    //         _info.dstPort = dstPort;
    //         _info.protocol = Protocol::TCP;
    //     }
    // };

    // class UDPServer : public SocketBase
    // {
    //     UDPServer(uint16_t listenPort = 8081)
    //     {
    //         _info.srcAddr = INADDR_ANY;
    //         _info.srcPort = listenPort;
    //         _info.protocol = Protocol::UDP;
    //     }
    // };

    // class UDPClient : public SocketBase
    // {
  
    // };
}




#endif