//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_HTTPLISTENER_H
#define REFERENCELIB_HTTPLISTENER_H


#include "../Request/Request.h"
#include "../../../container/Queue/BlockQueue.hpp"
#include "../../Selector/EpollSelector.h"

class HttpListener {
protected:
    BlockQueue<Request> requests;
    Pointer<EpollSelector> selector;
public:
    void run();
};


#endif //REFERENCELIB_HTTPLISTENER_H
