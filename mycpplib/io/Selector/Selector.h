//
// Created by 左钰 on 2019/12/15.
//

#ifndef MYCPPLIB_SELECTOR_H
#define MYCPPLIB_SELECTOR_H


#include <featurers/UnCopiable.h>
#include <io/Channel/Network/ServerSocketChannel.h>
#include <sys/epoll.h>
#include <containers/Queue/BlockQueue.hpp>

class Selector : public UnCopiable {
protected:
    ServerSocketChannel *listenChannel;
    int epfd;
    epoll_event epollEvent;

public:
    struct packet {
        SocketChannel channel;
        Buffer buffer;

        packet() = default;
        packet(SocketChannel &&channel, Buffer &&buffer);
        packet(const packet &rhs);
        packet(packet &&rhs) noexcept ;

        bool operator==(const packet &rhs) const ;
    };

protected:
    BlockQueue<packet> sending, coming;

    void removeEvent(SocketChannel &channel);
    void addEvent(int cfd);

public:
    explicit Selector(ServerSocketChannel *channel = nullptr);
    void run();

    packet pollPacket();
};


#endif //MYCPPLIB_SELECTOR_H
