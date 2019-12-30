//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_VIEW_H
#define REFERENCELIB_VIEW_H


#include "../../../base/Pointer.hpp"

class View : public Object {
protected:
    virtual Pointer<SString> getSuffix() = 0;
    virtual Pointer<SString> getPrefix() = 0;
public:
    virtual void send() = 0;
};


#endif //REFERENCELIB_VIEW_H
