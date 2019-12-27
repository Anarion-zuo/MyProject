//
// Created by 左钰 on 2019/12/15.
//

#include "EpollSelector.h"
#include <sys/epoll.h>
#include <unistd.h>
#include <exceptions/io/Network/EpollCreateException.h>
#include <netinet/in.h>
#include <exceptions/io/Network/EpollConfigException.h>
#include <exceptions/io/Network/EpollWaitException.h>
#include <exceptions/io/Network/AcceptException.h>

EpollSelector::EpollSelector(int maxConn) : epfd(::epoll_create(maxConn)), maxConnection(maxConn), all(Allocator::allocate<epoll_event>(maxConn)) {
    if (epfd == -1) {
        throw EpollCreateException();
    }

}

EpollSelector::EpollSelector(EpollSelector &&rhs) noexcept : epfd(rhs.epfd), maxConnection(rhs.maxConnection) {
    rhs.epfd = -1;
    rhs.maxConnection = 0;
}

EpollSelector::~EpollSelector() {
    ::close(epfd);
    Allocator::deallocate(all, maxConnection);
}

void EpollSelector::registerChannel(SocketChannel &channel, bool edgeTrigger) {
    lfd = channel.getSocketFd();
    event.events = EPOLLIN;
    event.data.fd = lfd;
    if (edgeTrigger) {
        event.events |= EPOLLET;
    }
    int ret;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &event);
    if (ret == -1) {
        throw EpollConfigException();
    }
}

void EpollSelector::wait() {
    int ret;
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int size = epoll_wait(epfd, all, maxConnection, -1);
    if (size < 0 && errno == EINTR) {
        throw EpollWaitException();
    }
    for (int i = 0; i < size; ++i) {
        if (all[i].data.fd == lfd) {
            int cfd = ::accept(lfd, reinterpret_cast<sockaddr*>(&client_addr), &client_len);
            if (cfd == -1) {
                throw AcceptException();
            }
            event.data.fd = cfd;
            event.events = EPOLLIN | EPOLLET;
            ret = epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &event);
            if (ret == -1) {
                throw EpollConfigException();
            }
        } else if (!(all[i].events & EPOLLIN)) {
            continue;
        } else {
            // handle
        }
    }
}
