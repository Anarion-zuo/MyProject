//
// Created by anarion on 2020/1/4.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include "IconController.h"

Pointer<SString> IconController::onGet(Pointer<Request> request, Pointer<Response> response,
                                       Pointer<HashMap<SString, SString>> attributes) {
    response->setCode(404);
    return Pointer<SString>();
}

Pointer<SString> IconController::onPost(Pointer<Request> request, Pointer<Response> response,
                                        Pointer<HashMap<SString, SString>> attributes) {
    return Pointer<SString>();
}

Pointer<SString> IconController::onDelete(Pointer<Request> request, Pointer<Response> response,
                                          Pointer<HashMap<SString, SString>> attributes) {
    return Pointer<SString>();
}

Pointer<SString> IconController::onPut(Pointer<Request> request, Pointer<Response> response,
                                       Pointer<HashMap<SString, SString>> attributes) {
    return Pointer<SString>();
}
