//
// Created by 左钰 on 2019/12/8.
//

#ifndef MYCPPLIB_POINTER_HPP
#define MYCPPLIB_POINTER_HPP

#include <featurers/UnCopiable.h>
#include <initializer_list>
#include <featurers/Hashable.h>

template <typename T>
class Pointer : public UnCopiable, public Hashable {
    friend class Allocator;
protected:
    T *ptr;
public:
    virtual ~Pointer() = default;

    explicit Pointer(T *ptr = nullptr) : ptr(ptr) {}

    Pointer(const Pointer<T> &rhs) : ptr(rhs.ptr) {}

    Pointer(Pointer<T> &&rhs) noexcept : ptr(rhs.ptr) {
        rhs.ptr = nullptr;
    }

    bool isNull() {
        return !ptr;
    }

    Pointer<T> &operator=(const Pointer<T> &rhs) {
        if (&rhs == this) {
            return *this;
        }
        ptr = rhs.ptr;
        return *this;
    }

    Pointer<T> &operator=(Pointer<T> &&rhs) noexcept {
        delete ptr;
        ptr = rhs.ptr;
        rhs.ptr = nullptr;
        return *this;
    }

    Pointer<T> &operator=(T *p) {
        ptr = p;
        return *this;
    }

    T &operator*() {
        return *ptr;
    }

    T *getPointer() {
        return ptr;
    }

    T *operator->() {
        return ptr;
    }

    bool operator==(const Pointer<T> &rhs) const {
        return ptr == rhs.ptr;
    }

    Pointer<T> &operator++() {
        ++ptr;
        return *this;
    }

    Pointer<T> &operator++(int) {
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


#endif //MYCPPLIB_POINTER_HPP
