//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_EPOLLSELECTOR_H
#define REFERENCELIB_EPOLLSELECTOR_H


#include "../../io/Channel/Network/tcp/TcpServerSocketChannel.h"
#include <sys/epoll.h>
#include "../../container/Queue/BlockQueue.hpp"

class EpollSelector {
protected:
    Pointer<TcpServerSocketChannel> listenChannel;
    int epfd;
    epoll_event epollEvent;

public:
    struct packet : public Object {
        Pointer<TcpSocketChannel> channel;
        Pointer<Buffer> buffer;

        packet() = default;
        packet(Pointer<TcpSocketChannel> channel, Pointer<Buffer> buffer);

    };

protected:
    BlockQueue<packet> sending, coming;

    void removeEvent(Pointer<TcpSocketChannel> channel);
    void addEvent(int cfd);

public:
    explicit EpollSelector(Pointer<TcpServerSocketChannel> channel);
    void run();

    Pointer<packet> pollPacket();
};


#endif //REFERENCELIB_EPOLLSELECTOR_H
