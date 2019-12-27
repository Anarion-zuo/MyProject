//
// Created by 左钰 on 2019/12/27.
//

#include "Selector.h"
#include <sys/epoll.h>
#include <exceptions/io/Network/EpollCreateException.h>
#include <exceptions/io/Network/EpollConfigException.h>

Selector::Selector(ServerSocketChannel *channel)  : listenChannel(channel), epfd(epoll_create(4096)) {
    // initialize epoll reactor
    if (epfd == -1) {
        throw EpollCreateException();
    }
    epollEvent.events = EPOLLIN;
    int lfd = listenChannel->getSocketFd()
    epollEvent.data.fd = lfd;
    int ret;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &epollEvent);
    if (ret == -1) {
        throw EpollConfigException();
    }
}

void Selector::run() {

}
