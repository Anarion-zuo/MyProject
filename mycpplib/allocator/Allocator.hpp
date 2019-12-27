//
// Created by 左钰 on 2019/12/5.
//

#ifndef MYCPPLIB_ALLOCATOR_HPP
#define MYCPPLIB_ALLOCATOR_HPP
#include <cstdlib>
#include <exceptions/Allocator/MemoryAllocationException.h>
#include "../erronos.h"
#include "Allocator.h"
#include <new>
#include <wrappers/Pointer/Pointer.hpp>

template <typename T> class Pointer;

class Allocator {
public:
    template <class T>
    static T *allocate() {
        int ret;
        T *p;
        ret = ::allocate(reinterpret_cast<char **>(&p), sizeof(T));
        if (ret != stat_noerr) {
            throw MemoryAllocationException();
        }
        return p;
    }

    template <class T>
    static T *allocate(size_t n) {
        int ret;
        T *p;
        ret = ::allocate(reinterpret_cast<char **>(&p), sizeof(T) * n);
        if (ret != stat_noerr) {
            throw MemoryAllocationException();
            return nullptr;
        }
        return p;
    }

    template <class T>
    static void deallocate(T *&p) {
        if (p)
            p->~T();
        else
            return;
        ::deallocate(p, sizeof(T));
        p = nullptr;
    }

    template <typename T> static void deallocate(Pointer<T> &p) {
        deallocate(p.ptr);
    }

    template <class T> static void deallocate(T *&p, unsigned long nsize) {
        T *pp = p;
        for (; pp - p != nsize; ++pp) {
            pp->~T();
        }
        ::deallocate(p, sizeof(T) * nsize);
        p = nullptr;
    }

    static void deallocate(int *&p, unsigned long nsize) {
        ::deallocate(p, sizeof(int) * nsize);
        p = nullptr;
    }

    static void deallocate(char *&p, unsigned long nsize) {
        ::deallocate(p, sizeof(char) * nsize);
        p = nullptr;
    }

    static void deallocate(unsigned int *&p, unsigned long nsize) {
        ::deallocate(p, sizeof(unsigned int) * nsize);
        p = nullptr;
    }

    static void deallocate(unsigned char *&p, unsigned long nsize) {
        ::deallocate(p, sizeof(unsigned char) * nsize);
        p = nullptr;
    }

    static void deallocate(short *&p, unsigned long nsize) {
        ::deallocate(p, sizeof(short) * nsize);
        p = nullptr;
    }

    static void deallocate(unsigned short *&p, unsigned long nsize) {
        ::deallocate(p, sizeof(unsigned short) * nsize);
        p = nullptr;
    }

    static void deallocate(long *&p, unsigned long nsize) {
        ::deallocate(p, sizeof(long) * nsize);
        p = nullptr;
    }

    static void deallocate(unsigned long *&p, unsigned long nsize) {
        ::deallocate(p, sizeof(unsigned long) * nsize);
        p = nullptr;
    }

    static void deallocate(float *&p, unsigned long nsize) {
        ::deallocate(p, sizeof(float) * nsize);
        p = nullptr;
    }

    static void deallocate(double *&p, unsigned long nsize) {
        ::deallocate(p, sizeof(double) * nsize);
        p = nullptr;
    }

    static void deallocate(long double *&p, unsigned long nsize) {
        ::deallocate(p, sizeof(long double) * nsize);
        p = nullptr;
    }

    template <typename T>
    static void deallocate(T &rhs) {
        deallocate(&rhs);
    }
};

#endif //MYCPPLIB_ALLOCATOR_HPP
