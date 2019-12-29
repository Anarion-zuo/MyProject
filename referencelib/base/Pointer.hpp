//
// Created by anarion on 2019/12/29.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_POINTER_HPP
#define REFERENCELIB_POINTER_HPP

template <typename T>
class Pointer {
protected:
    T *ptr;

public:
    explicit Pointer(T *ptr) : ptr(ptr) {}

    bool operator==(const Pointer<T> &rhs) const {
        return ptr == rhs.ptr;
    }

    Pointer<T> &operator=(T *rhs) {
        ptr = rhs;
        return *this;
    }

    Pointer<T> &operator=(const Pointer<T> &rhs) {
        if (&rhs == this) {
            return *this;
        }
        ptr = rhs.ptr;
        return *this;
    }

    T *operator->() {
        return ptr;
    }

    T &operator*() {
        return *ptr;
    }

    Pointer<T> &operator++() {
        ++ptr;
        return *this;
    }

    Pointer<T> operator++(int) {
        ++ptr;
        return *this;
    }

    Pointer<T> &operator--() {
        --ptr;
        return *this;
    }

    Pointer<T> &operator--(int) {
        --ptr;
        return *this;
    }

    Pointer<T> operator+(unsigned long step) const {
        return ptr + step;
    }

    Pointer<T> operator-(unsigned long step) const {
        return ptr - step;
    }

    long operator-(const Pointer<T> &rhs) const {
        return ptr - rhs.ptr;
    }
};


#endif //REFERENCELIB_POINTER_HPP
