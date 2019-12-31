//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_SERVERSOCKETCHANNEL_H
#define REFERENCELIB_SERVERSOCKETCHANNEL_H


#include "SocketChannel.h"
#include "../../../base/Number.hpp"
#include "../../../container/Set/HashSet.hpp"

class ServerSocketChannel : public SocketChannel {
protected:
    sockaddr_in myAddr;
public:
    explicit ServerSocketChannel(in_port_t port = 80) {
        memset(&myAddr, 0, sizeof(sockaddr_in));
        myAddr.sin_family = AF_INET;
        myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        bind(port);
    }

    void bind(in_port_t host_port);
    void listen(int backlog = 128);
    Pointer<SocketChannel> accept() ;
    void setNonBlock();
};


#endif //REFERENCELIB_SERVERSOCKETCHANNEL_H
