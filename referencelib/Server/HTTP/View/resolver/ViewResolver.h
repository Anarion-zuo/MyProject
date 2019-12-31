//
// Created by anarion on 2019/12/31.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_VIEWRESOLVER_H
#define REFERENCELIB_VIEWRESOLVER_H


#include "../../../../base/Pointer.hpp"
#include "../../../../container/Map.hpp"

class ViewResolver {
protected:

public:
    virtual void run(Pointer<SocketChannel> channel) = 0;

};


#endif //REFERENCELIB_VIEWRESOLVER_H
