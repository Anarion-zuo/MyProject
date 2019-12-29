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
    virtual void add(T *p, size_type index) = 0;
    virtual T *get(size_type index) = 0;

    virtual size_type size() const = 0;

    virtual size_type indexOf(T *p) = 0;
    size_type lastIndexOf(T *p) {
        return size() - indexOf(p) - 1;
    }

};


#endif //REFERENCELIB_LIST_H
