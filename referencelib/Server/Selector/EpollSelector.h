//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_EPOLLSELECTOR_H
#define REFERENCELIB_EPOLLSELECTOR_H


#include "../../io/Channel/Network/ServerSocketChannel.h"
#include <sys/epoll.h>
#include "../../container/Queue/BlockQueue.hpp"

class EpollSelector {
protected:
    Pointer<ServerSocketChannel> listenChannel;
    int epfd;
    epoll_event epollEvent;

public:
    struct packet : public Object {
        Pointer<SocketChannel> channel;
        Pointer<Buffer> buffer;

        packet() = default;
        packet(Pointer<SocketChannel> channel, Pointer<Buffer> buffer);

    };

protected:
    BlockQueue<packet> sending, coming;

    void removeEvent(Pointer<SocketChannel> channel);
    void addEvent(int cfd);

public:
    explicit EpollSelector(Pointer<ServerSocketChannel> channel);
    void run();

    Pointer<packet> pollPacket();
};


#endif //REFERENCELIB_EPOLLSELECTOR_H
