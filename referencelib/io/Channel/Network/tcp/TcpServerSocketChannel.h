//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_TCPSERVERSOCKETCHANNEL_H
#define REFERENCELIB_TCPSERVERSOCKETCHANNEL_H


#include "TcpSocketChannel.h"
#include "../../../../base/Number.hpp"
#include "../../../../container/Set/HashSet.hpp"
#include "../ServerSocketChannel.h"

class TcpServerSocketChannel : public TcpSocketChannel, public ServerSocketChannel {
protected:
    sockaddr_in myAddr;
public:
    explicit TcpServerSocketChannel(in_port_t port = 80) {
        memset(&myAddr, 0, sizeof(sockaddr_in));
        myAddr.sin_family = AF_INET;
        myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        bind(port);
    }

    void bind(in_port_t host_port);
    void listen(int backlog = 128);
    Pointer<TcpSocketChannel> accept() ;
    void setNonBlock();

    void write(Pointer<Buffer> buffer) override;

    void read(Pointer<Buffer> buffer) override;

    size_type write(char *arr, size_type num) override;

    size_type read(char *arr, size_type num) override;
};


#endif //REFERENCELIB_TCPSERVERSOCKETCHANNEL_H
