//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include "Cookie.h"

void Cookie::add(Pointer<SString> key, Pointer<SString> val) {
    map.put(key, val);
}

void Cookie::send(Pointer<SocketChannel> channel) {
    auto it = map.getBeginIterator();
    while (it->hasNext()) {
        auto en = it->next();
        Pointer<SString> key = en->getVal();
        Pointer<SString> val = en->getKey();
        char blank = ' ', co = ';', eq = '=';
        channel->read(const_cast<char*>(key->cstr()), key->length());
        channel->read(&eq, 1);
        channel->read(const_cast<char*>(val->cstr()), val->length());
        channel->read(&co, 1);
        channel->read(&blank, 1);
    }
}
