//
// Created by 左钰 on 2019/12/15.
//

#ifndef MYCPPLIB_EPOLLSELECTOR_H
#define MYCPPLIB_EPOLLSELECTOR_H

#include <base-classes/Object.h>
#include <io/Channel/Network/SocketChannel.h>
#include <sys/epoll.h>
#include "Selector.h"

class EpollSelector : public Selector {
protected:
    int epfd, maxConnection, lfd;
    epoll_event event, *all;
public:
    explicit EpollSelector(int maxConn);
    EpollSelector(EpollSelector &&rhs) noexcept ;
    ~EpollSelector() override;

    void registerChannel(SocketChannel &channel, bool edgeTrigger);
    void wait();
};


#endif //MYCPPLIB_EPOLLSELECTOR_H
