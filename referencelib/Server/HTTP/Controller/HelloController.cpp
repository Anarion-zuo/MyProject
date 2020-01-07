//
// Created by anarion on 2020/1/4.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include "HelloController.h"

Pointer<SString> HelloController::onGet(Pointer<Request> request, Pointer<Response> response,
                                        Pointer<HashMap<SString, SString>> attributes) {
    attributes->put(new SString("xx"), new SString("this is an anttribute"));
    Pointer<SString> key = SString::copyFromStack("y3");
    attributes->put(new SString("argument"), request->getParam(key));
    return new SString("hello");
}

Pointer<SString> HelloController::onPost(Pointer<Request> request, Pointer<Response> response,
                                         Pointer<HashMap<SString, SString>> attributes) {
    return Pointer<SString>();
}

Pointer<SString> HelloController::onDelete(Pointer<Request> request, Pointer<Response> response,
                                           Pointer<HashMap<SString, SString>> attributes) {
    return Pointer<SString>();
}

Pointer<SString> HelloController::onPut(Pointer<Request> request, Pointer<Response> response,
                                        Pointer<HashMap<SString, SString>> attributes) {
    return Pointer<SString>();
}
