//
// Created by 左钰 on 2019/12/27.
//

#include "Selector.h"
#include <exceptions/io/Network/EpollCreateException.h>
#include <exceptions/io/Network/EpollConfigException.h>
#include <exceptions/io/Network/AcceptException.h>
#include <unistd.h>
#include <exceptions/io/File/CloseFileException.h>

Selector::Selector(ServerSocketChannel *channel)  : listenChannel(channel), epfd(epoll_create(4096)) {
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

void Selector::run() {
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
                Buffer buffer(1024);
                SocketChannel client {fd};
                buffer.put(fd);
                if (buffer.writtenSize() == 0) {
                    // close connection
                    removeEvent(client);
                } else {
                    coming.put(packet(std::move(client), std::move(buffer)));
                }
            }
        }
    }
}

void Selector::removeEvent(SocketChannel &channel) {
    epoll_event event;
    event.events = EPOLLIN;
    int fd = channel.getSocketFd();
    event.data.fd = fd;
    int ret;
    ret = ::close(fd);
    if (ret == -1) {
        throw CloseFileException();
    }
    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &event);
    if (ret == -1) {
        throw EpollConfigException();
    }
}

void Selector::addEvent(int cfd) {
    epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = cfd;
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &event);
    if (ret == -1) {
        throw EpollConfigException();
    }
}

Selector::packet Selector::pollPacket() {
    return coming.poll();
}

Selector::packet::packet(SocketChannel &&channel, Buffer &&buffer) : channel(std::forward<SocketChannel>(channel)), buffer(std::forward<Buffer>(buffer)) {

}

Selector::packet::packet(Selector::packet &&rhs) noexcept : channel(std::move(rhs.channel)), buffer(std::move(rhs.buffer)) {}

bool Selector::packet::operator==(const Selector::packet &rhs) const {
    return &rhs == this;
}

Selector::packet::packet(const Selector::packet &rhs) : channel(rhs.channel), buffer(0) {

}
