//
// Created by 左钰 on 2019/12/15.
//

#ifndef MYCPPLIB_SELECTOR_H
#define MYCPPLIB_SELECTOR_H


#include <featurers/UnCopiable.h>
#include <io/Channel/Network/ServerSocketChannel.h>

class Selector : public UnCopiable {
protected:
    ServerSocketChannel *listenChannel;
    int epfd;
    epoll_event epollEvent;
public:
    explicit Selector(ServerSocketChannel *channel = nullptr);
    void run();
};


#endif //MYCPPLIB_SELECTOR_H
