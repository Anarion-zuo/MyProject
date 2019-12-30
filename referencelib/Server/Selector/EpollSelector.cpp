//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include <zconf.h>
#include "EpollSelector.h"
#include "../../exceptions/system/EpollExceptions.h"
#include "../../exceptions/system/AcceptException.h"
#include "../../exceptions/system/CloseFdException.h"

EpollSelector::EpollSelector(Pointer<ServerSocketChannel> channel)  : listenChannel(channel), epfd(epoll_create(4096)) {
    // initialize epoll reactor
    if (epfd == -1) {
        throw EpollCreateException();
    }
    listenChannel->setNonBlock();
    epollEvent.events = EPOLLIN | EPOLLET;
    int lfd = listenChannel->getSocketFd();
    epollEvent.data.fd = lfd;
    int ret;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &epollEvent);
    if (ret == -1) {
        throw EpollConfigException();
    }
}

void EpollSelector::run() {
    int fd, i, waitret;
    int lfd = listenChannel->getSocketFd();
    epoll_event events[4096];
    while (true) {
        waitret = epoll_wait(epfd, events, 4096, -1);
        for (i = 0; i < waitret; ++i) {
            fd = events[i].data.fd;
            if (!(events[i].events & EPOLLIN)) {
                continue;
            }
            // accept
            if (fd == lfd) {
                int cfd;
                sockaddr_in cli_addr{};
                socklen_t addrlen;
                cfd = accept(lfd, reinterpret_cast<sockaddr*>(&cli_addr), &addrlen);
                if (cfd == -1) {
                    throw AcceptException();
                }
                addEvent(cfd);
            } else {   // read
                Pointer<Buffer> buffer = Buffer::allocate(4096);
                Pointer<SocketChannel> client = new SocketChannel {fd};
                buffer->put(fd);
                if (buffer->writtenSize() == 0) {
                    // close connection
                    removeEvent(client);
                } else {
                    coming.put(new packet(client, buffer));
                }
            }
        }
    }
}

void EpollSelector::removeEvent(Pointer<SocketChannel> channel) {
    epoll_event event;
    event.events = EPOLLIN;
    int fd = channel->getSocketFd();
    event.data.fd = fd;
    int ret;
    ret = ::close(fd);
    if (ret == -1) {
        throw CloseFdException();
    }
    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &event);
    if (ret == -1) {
//        throw EpollConfigException();
    }
}

void EpollSelector::addEvent(int cfd) {
    epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = cfd;
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &event);
    if (ret == -1) {
        throw EpollConfigException();
    }
}

Pointer<EpollSelector::packet> EpollSelector::pollPacket() {
    return coming.poll();
}

EpollSelector::packet::packet(Pointer<SocketChannel> channel, Pointer<Buffer> buffer) : channel(channel), buffer(buffer) {

}

