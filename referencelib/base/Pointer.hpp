//
// Created by anarion on 2019/12/29.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_POINTER_HPP
#define REFERENCELIB_POINTER_HPP

#include <cstddef>
#include "Object.h"

template <typename T>
class Pointer {
protected:
    T *ptr;

public:
    Pointer() : ptr(nullptr) {}
    Pointer(std::nullptr_t p) : ptr(p) {}
    template <typename V> Pointer(V *ptr) : ptr(reinterpret_cast<T*>(ptr)) {}

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
        if ((Pointer<T>*)(&rhs) == this) {
            return *this;
        }
        ptr = (T*)((const_cast<Pointer<V>&>(rhs)).operator->());
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
