//
// Created by anarion on 2019/12/19.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef MYCPPLIB_REFERENCE_HPP
#define MYCPPLIB_REFERENCE_HPP


#include "Pointer.hpp"

template <typename T>
class Reference : public Pointer<T> {
public:
    explicit Reference(T *p = nullptr) : Pointer<T>(p) {}
    ~Reference() override {
        delete Pointer<T>::ptr;
    }

    Reference(Reference<T> &&rhs) noexcept : Pointer<T>(rhs.ptr) {
        rhs.ptr = nullptr;
    }

    Reference<T> &operator=(Reference<T> &&rhs) noexcept {
        delete this->ptr;
        this->ptr = rhs.ptr;
        rhs.ptr = nullptr;
        return *this;
    }

    Reference<T> &operator=(T *&p) {
        delete this->ptr;
        this->ptr = p;
        p = nullptr;
        return *this;
    }
};


#endif //MYCPPLIB_REFERENCE_HPP
