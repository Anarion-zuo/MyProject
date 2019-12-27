//
// Created by 左钰 on 2019/12/15.
//

#ifndef MYCPPLIB_SELECTABLECHANNEL_H
#define MYCPPLIB_SELECTABLECHANNEL_H


#include "Channel.h"

class SocketChannel;

class SelectableChannel : public Channel {
public:
    virtual int getFd() = 0;
    virtual void run() = 0;
    virtual SocketChannel accept() = 0;
};


#endif //MYCPPLIB_SELECTABLECHANNEL_H
