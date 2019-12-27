//
// Created by 左钰 on 2019/12/15.
//

#ifndef MYCPPLIB_SERVERSOCKETCHANNEL_H
#define MYCPPLIB_SERVERSOCKETCHANNEL_H

#include <netinet/in.h>
#include "SocketChannel.h"
#include <wrappers/Number.hpp>

class ServerSocketChannel : public SocketChannel, public SelectableChannel {
protected:
    sockaddr_in myAddr;
    HashSet<Number<int>> connectedHosts;
public:
    explicit ServerSocketChannel(in_port_t port = 80) {
        memset(&myAddr, 0, sizeof(sockaddr_in));
        myAddr.sin_family = AF_INET;
        myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        bind(port);
    }

    void bind(in_port_t host_port);
    void listen(int backlog = 128);
    SocketChannel accept() override ;
    void setNonBlock();
};


#endif //MYCPPLIB_SERVERSOCKETCHANNEL_H
