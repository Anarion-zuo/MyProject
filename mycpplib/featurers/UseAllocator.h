//
// Created by 左钰 on 2019/12/9.
//

#ifndef MYCPPLIB_USEALLOCATOR_H
#define MYCPPLIB_USEALLOCATOR_H

#include <allocator/Allocator.hpp>

class UseAllocator {
public:
    static void *operator new(unsigned long count) {
        int ret;
        void *p;
        ret = ::allocate(reinterpret_cast<char **>(&p), count);
        if (ret != stat_noerr) {
            throw MemoryAllocationException();
        }
        return p;
    }

    static void *operator new[](unsigned long count) {
        int ret;
        void *p;
        ret = ::allocate(reinterpret_cast<char **>(&p), count);
        if (ret != stat_noerr) {
            throw MemoryAllocationException();
        }
        return p;
    }

    static void operator delete(void *p, unsigned long count) {
        ::deallocate(p, count);
    }

    static void operator delete[](void *p, unsigned long count) {
        ::deallocate(p, count);
    }
};


#endif //MYCPPLIB_USEALLOCATOR_H
