//
// Created by anarion on 2019/12/28.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_REFERENCE_HPP
#define REFERENCELIB_REFERENCE_HPP

#include "Object.h"

template <typename T>
class Reference {
    struct package {
        T *pointer;
        size_type count;

        explicit package(T *pointer) : pointer(pointer), count(1) {}

        ~package() {
            delete pointer;
        }
    };
protected:
    package *pack;

    void tryDelete() {
        if (pack->count == 0) {
            delete pack;
        }
    }

public:
    explicit Reference(T *p) : pack(new package(p)) {}

    Reference(const Reference &rhs) : pack(rhs.pack) {
        ++rhs.pack->count;
    }

    Reference(Reference &&rhs) noexcept : pack(rhs.pack) {
        rhs.pack = nullptr;
    }

    ~Reference() {
        if (pack->count == 1) {
            delete pack;
        } else {
            --pack->count;
        }
    }

    Reference<T> &operator=(const Reference<T> &rhs) {
        if (&rhs == this) {
            return *this;
        }
        --pack->count;
        tryDelete();
        pack = rhs.pack;
        ++pack->count;
        return *this;
    }

    Reference<T> &operator=(Reference<T> &&rhs) {
        pack = rhs.pack;
        rhs.pack = nullptr;
        return *this;
    }
};

//extern Reference<Object> Null =

#endif //REFERENCELIB_REFERENCE_HPP
