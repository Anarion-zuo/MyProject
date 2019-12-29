//
// Created by anarion on 2019/12/29.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_POINTER_HPP
#define REFERENCELIB_POINTER_HPP

#include "Object.h"

template <typename T>
class Pointer {
protected:
    T *ptr;

public:
    Pointer() : ptr(nullptr) {}
    Pointer(T *ptr) : ptr(ptr) {}

    template <typename V>
    bool operator==(const Pointer<V> &rhs) const {
        return ptr == reinterpret_cast<T*>(rhs.ptr);
    }

    template <typename V>
    Pointer<T> &operator=(V *rhs) {
        ptr = reinterpret_cast<T*>(rhs);
        return *this;
    }

    template <typename V>
    Pointer<T> &operator=(const Pointer<V> &rhs) {
        if (&rhs == this) {
            return *this;
        }
        ptr = reinterpret_cast<T*>(rhs);
        return *this;
    }

    bool isNull() const {
        return ptr;
    }

    T *operator->() {
        return ptr;
    }

    T &operator*() {
        return *ptr;
    }

    void release() {
        delete ptr;
        ptr = nullptr;
    }
};

#endif //REFERENCELIB_POINTER_HPP
