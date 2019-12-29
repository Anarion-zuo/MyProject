//
// Created by anarion on 2019/12/29.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_CONTAINER_H
#define REFERENCELIB_CONTAINER_H


#include "../base/Object.h"
#include "../base/Pointer.hpp"

template <typename T>
class Container : public Object {
public:
    virtual void add(Pointer<T> p) = 0;
    virtual void addAll(Pointer<Container<T>> rhs) = 0;

    virtual void remove(Pointer<T> p) = 0;
    virtual void removeAll(Pointer<Container<T>> rhs) = 0;
};


#endif //REFERENCELIB_CONTAINER_H
