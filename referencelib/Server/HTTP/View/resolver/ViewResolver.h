//
// Created by anarion on 2019/12/31.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_VIEWRESOLVER_H
#define REFERENCELIB_VIEWRESOLVER_H


#include "../../../../base/Pointer.hpp"
#include "../../../../container/Map.hpp"
#include "../../../../io/Channel/Network/tcp/TcpSocketChannel.h"

class ViewResolver {
protected:

public:
    virtual void send(Pointer<TcpSocketChannel> channel) = 0;
    virtual void loadView() = 0;
    virtual size_type getContentSize() = 0;
};


#endif //REFERENCELIB_VIEWRESOLVER_H
