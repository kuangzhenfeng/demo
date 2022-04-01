#ifndef __MY_SOCKET_H__
#define __MY_SOCKET_H__


#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "common.h"

class MySocketTest : public ModuleBase
{
public:
    MySocketTest() : ModuleBase(MODULE_SOCKET, "MODULE_SOCKET"){};
    int test();
};

namespace my_socket
{ 
    enum class Protocol
    {
        TCP,
        UDP,
    };

    typedef struct
    {
        uint32_t srcAddr;
        uint16_t srcPort;
        uint32_t  dstAddr;
        uint16_t dstPort;
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
            srcAddr.sin_port = htons(_info.srcPort);
            srcAddr.sin_addr.s_addr = htonl(_info.srcAddr);
            bind(listenFd, reinterpret_cast<sockaddr *>(&srcAddr), sizeof(srcAddr));
        }


        SocketInfo _info;
    };

    class TCPServer : public SocketBase
    {
        // TCPServer(int listenPort = 8080) : _srcAddr(INADDR_ANY), _srcPort(listenPort), _protocol(Protocol::TCP){}
        TCPServer(int listenPort = 8080)
        {
            _info.srcAddr = INADDR_ANY;
            _info.srcPort = listenPort;
            _info.protocol = Protocol::TCP;
        }
        // void start() override
        // {

        // }
    };

    class TCPClient : public SocketBase
    {
        TCPClient(uint32_t dstAddr, uint16_t dstPort)
        {
            _info.dstAddr = dstAddr;
            _info.dstPort = dstPort;
            _info.protocol = Protocol::TCP;
        }
    };

    class UDPServer : public SocketBase
    {
        UDPServer(uint16_t listenPort = 8081)
        {
            _info.srcAddr = INADDR_ANY;
            _info.srcPort = listenPort;
            _info.protocol = Protocol::UDP;
        }
    };

    class UDPClient : public SocketBase
    {
  
    };
}




#endif