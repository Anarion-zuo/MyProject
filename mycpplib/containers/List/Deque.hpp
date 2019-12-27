//
// Created by anarion on 2019/11/7.
//

#ifndef MYSTL_DEQUE_HPP
#define MYSTL_DEQUE_HPP


#include <base-classes/Object.h>
#include <exceptions/containers/IndexOutOfRangeException.h>
#include "containers/List/Vector.hpp"
#include "DoublyList.hpp"

template <
        typename Obj,
        unsigned long blockSize = 8
                >
class Deque : public Object {
    typedef unsigned long size_type;

    struct block {
        void copy_back_n(size_type n) {
            // n cannot be larger than spare space
            Obj *p = end - 1, *pn = p + n;
            for (; p != arr - 1; --p, --pn) {
                ::new (pn) Obj(std::move(*p));
            }
        }

        Obj *arr = Allocator::allocate<Obj>(blockSize);
        Obj *end = arr;

        explicit block(size_type size = 0) {
            end += size;
        }

        // guarantee size is not greater than blockSize
        explicit block(const Obj &obj, size_type size = 0) {
            end += size;
            for (size_type i = 0; i < size; ++i) {
                ::new (&arr[i]) Obj(obj);
            }
        }

        explicit block(Obj &&obj, size_type size = 0) {
            end += size;
            for (size_type i = 0; i < size; ++i) {
                ::new (&arr[i]) Obj(std::forward<Obj>(obj));
            }
        }

        block(const block &rhs) {
            end += rhs.size();
            auto p = arr, *rp = rhs.arr;
            while (p != end) {
                ::new (p) Obj(*rp);
            }
        }

        block(block &&rhs) noexcept : arr(rhs.arr), end(rhs.end) {
            rhs.arr = Allocator::allocate<Obj>(blockSize);
            rhs.end = rhs.arr;
        }

        ~block() {
            Allocator::deallocate(arr, size());
        }

        size_type size() {
            return end - arr;
        }

        void pushBack(const Obj &obj) {
            ::new (end) Obj(obj);
            ++end;
        }

        void pushBack(Obj &&obj) {
            ::new (end) Obj(std::forward<Obj>(obj));
            ++end;
        }

        void pushFront(const Obj &obj) {
            copy_back_n(1);
            ::new (arr) Obj(obj);
        }

        void pushFront(Obj &&obj) {
            copy_back_n(1);
            ::new (arr) Obj(std::forward<Obj>(obj));
        }

        bool isFull() {
            return size() >= blockSize;
        }
    };

protected:
    Vector<block> heads;
    size_type count = 0;

    void expandBack() {
        heads.pushBack(block());
    }

    void expandFront() {
        heads.pushFront(block());
    }
public:
    explicit Deque(size_type nsize = 1) : heads(block(), nsize / blockSize + 1) {
        if (nsize == 0) {
            nsize = 1;
        }
    }

    explicit Deque(const Obj &obj, size_type nsize = 1) {
        if (nsize == 0) {
            nsize = 1;
        }
        size_type headsize = nsize / blockSize + 1, moresize = nsize % blockSize;
        for (size_type i = 0; i < headsize - 1; ++i) {
            block *bp = Allocator::allocate<block>();
            ::new (bp) block(obj, blockSize);
            heads.pushBack(bp);
        }
        block *bp = Allocator::allocate<block>();
        ::new (bp) block(obj, moresize);
        heads.pushBack(bp);
    }

    explicit Deque(const Deque<Obj> &rhs) : heads(rhs.heads), count(rhs.count) {}

    explicit Deque(Deque<Obj> &&rhs) noexcept : heads(std::move(rhs.heads)), count(rhs.count) {
        rhs.count = 0;
    }

    void pushBack(const Obj &obj) {
        block *backBlock = heads.back();
        if (backBlock->isFull()) {
            expandBack();
            backBlock = heads.back();
        }
        backBlock->pushBack(obj);
        ++count;
    }

    void pushBack(Obj &&obj) {
        block *backBlock = heads.back();
        if (backBlock->isFull()) {
            expandBack();
            backBlock = heads.back();
        }
        backBlock->pushBack(std::forward<Obj>(obj));
        ++count;
    }

    void pushFront(const Obj &obj) {
        block *frontBlock = heads.front();
        if (frontBlock->isFull()) {
            expandFront();
            frontBlock = heads.front();
        }
        frontBlock->pushFront(obj);
        ++count;
    }

    void pushFront(Obj &&obj) {
        block *frontBlock = heads.front();
        if (frontBlock->isFull()) {
            expandFront();
            frontBlock = heads.front();
        }
        frontBlock->pushFront(std::forward<Obj>(obj));
        ++count;
    }

    const Obj &operator[](size_type index) {
        if (index >= count) {
            throw IndexOutOfRangeException();
        }
        size_type firstSize = heads.front()->size();
        if (firstSize < blockSize) {
            if (index < firstSize) {
                return heads.front()->operator[](index);
            }
            index -= firstSize;
        }
        size_type blockIndex = index / blockSize, innerIndex = index % blockSize;
        if (firstSize < blockSize) {
            ++blockIndex;
        }
        return heads[blockIndex]->arr[innerIndex];
    }

};


#endif //MYSTL_DEQUE_HPP
