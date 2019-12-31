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
#include "../../../container/Queue/ListQueue.h"

class HtmlResolver;
class Controller {
protected:


    static Pointer<Map<Request, Controller>> controls;
    static void init();
    static void dispatchOne(Pointer<Request> request);

    Pointer<HtmlResolver> run(Pointer<Request> request, Pointer<Response> response);
public:
    virtual Pointer<SString> onGet(Pointer<Request> request, Pointer<Response> response) = 0;
    virtual Pointer<SString> onPost(Pointer<Request> request, Pointer<Response> response) = 0;
    virtual Pointer<SString> onDelete(Pointer<Request> request, Pointer<Response> response) = 0;
    virtual Pointer<SString> onPut(Pointer<Request> request, Pointer<Response> response) = 0;
};


#endif //REFERENCELIB_CONTROLLER_H
