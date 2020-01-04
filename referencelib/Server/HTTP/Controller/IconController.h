//
// Created by anarion on 2020/1/4.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_ICONCONTROLLER_H
#define REFERENCELIB_ICONCONTROLLER_H


#include "Controller.h"

class IconController : public Controller {
public:
    Pointer<SString>onGet(Pointer<Request> request, Pointer<Response> response, Pointer<HashMap<SString, SString>> attributes) override;

    Pointer<SString> onPost(Pointer<Request> request, Pointer<Response> response, Pointer<HashMap<SString, SString>> attributes) override;

    Pointer<SString> onDelete(Pointer<Request> request, Pointer<Response> response, Pointer<HashMap<SString, SString>> attributes) override;

    Pointer<SString> onPut(Pointer<Request> request, Pointer<Response> response, Pointer<HashMap<SString, SString>> attributes) override;
};


#endif //REFERENCELIB_ICONCONTROLLER_H
