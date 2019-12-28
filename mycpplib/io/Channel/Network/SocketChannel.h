//
// Created by 左钰 on 2019/12/15.
//

#ifndef MYCPPLIB_SOCKETCHANNEL_H
#define MYCPPLIB_SOCKETCHANNEL_H

#include <sys/socket.h>
#include <cstring>
#include <exceptions/io/Network/SocketCreateException.h>
#include <containers/Set/HashSet.hpp>
#include "../Channel.h"
#include "io/Buffer/Buffer.h"
#include <netinet/in.h>

class SocketChannel : public Channel {
protected:
    int sockfd;
public:
    SocketChannel()
    : sockfd(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) {    // use TCP
        if(sockfd == -1) {
            throw SocketCreateException();
        }
    }

    explicit SocketChannel(int fd)
    : sockfd(fd) {}

    SocketChannel(const SocketChannel &rhs) : sockfd(rhs.sockfd) {}

    SocketChannel(SocketChannel &&rhs) noexcept
    : sockfd(rhs.sockfd) {
        rhs.sockfd = -1;
    }

    ~SocketChannel() override ;

    int getSocketFd() const ;

    bool operator==(const SocketChannel &rhs) const ;

    bool isValid();

    void connect(const char *host_ip, in_port_t host_port);

    void write(Buffer &buffer) override;

    void read(Buffer &buffer) override;

    size_type write(char *arr, size_type num) override;

    size_type read(char *arr, size_type num) override;
};


#endif //MYCPPLIB_SOCKETCHANNEL_H
