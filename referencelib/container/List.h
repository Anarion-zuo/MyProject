//
// Created by anarion on 2019/12/29.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_LIST_H
#define REFERENCELIB_LIST_H

#include "Container.h"

template <typename T>
class List : public Container<T> {
public:
    virtual void add(Pointer<T> p) = 0;
    virtual void addAll(Pointer<Container<T>> rhs) = 0;
    virtual void add(Pointer<T> p, size_type index) = 0;
    virtual void addFirst(Pointer<T> p) = 0;
    virtual Pointer<T> get(size_type index) = 0;
    virtual Pointer<T> poll() = 0;

    virtual size_type indexOf(Pointer<Object> p) = 0;

};


#endif //REFERENCELIB_LIST_H
