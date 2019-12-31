//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_CONTROLLER_H
#define REFERENCELIB_CONTROLLER_H


#include "../../../container/SString.h"
#include "../../../base/Pointer.hpp"
#include "../Request/Request.h"
#include "../Response/Response.h"

class Controller {
protected:
    Pointer<SString> pattern = new SString;
    Pointer<Request> request;
    Pointer<Response> response;

    void run();
public:
    virtual Pointer<SString> onGet() = 0;
    virtual Pointer<SString> onPost() = 0;
    virtual Pointer<SString> onDelete() = 0;
    virtual Pointer<SString> onPut() = 0;
};


#endif //REFERENCELIB_CONTROLLER_H
