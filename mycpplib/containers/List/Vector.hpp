//
// Created by anarion on 2019/11/6.
//

#ifndef MYSTL_VECTOR_HPP
#define MYSTL_VECTOR_HPP

#include <exceptions/containers/IndexOutOfRangeException.h>
#include <exceptions/containers/EmptyContainerException.h>
#include <base-classes/Object.h>
#include <allocator/Allocator.hpp>
#include "List.hpp"
#include "SString.h"


template <typename Obj>
class Vector : public List<Obj>, public UseAllocator, public Hashable {
    friend class Buffer;
protected:
    typedef unsigned long size_type;

    // data
    Obj * begin = nullptr, *end = nullptr, *cur = nullptr;

    void allocate_new_size(size_type nsize) {
        begin = Allocator::allocate<Obj>(nsize);
        end = begin + nsize;
    }

    void expand() {
        size_type old_size = capacity(), new_size = old_size << 1ul;
        Obj * p = Allocator::allocate<Obj>(new_size);
        for (size_type i = 0; i < old_size; ++i) {
            ::new(&p[i]) Obj(std::move(begin[i]));
        }
        Allocator::deallocate<Obj>(begin, old_size);
        begin = p;
        end = begin + new_size;
        cur = begin + old_size;
    }

    void squeeze() {
        // return space when less than 1/3
        size_type del_size = capacity() / 3 * 2;
        end -= del_size;
        Allocator::deallocate(end, del_size);
    }

    // not duplicating but moving
    void copy_mem_move(Obj * src, Obj * dst, size_type nsize) {
        for (size_type i = 0; i < nsize; ++i) {
            ::new (&dst[i]) Obj(std::move(src[i]));
        }
    }

    // duplicating not moving
    void copy_mem_dup(Obj *src, Obj *dst, size_type nsize) {
        for (size_type i = 0; i < nsize; ++i) {
            ::new (&dst[i]) Obj(src[i]);
        }
    }

    /*
     * The following methods' index arguments are meant for copyings to begin at it,
     * not after it!!!
     * The copyings are for giving space, therefore are moving!!!
     * Assuming having sufficient space for the copyings!!!
     * No safe checking!!!
     */

    void copy_back_n(size_type index, size_type num) {
        Obj * ptr = cur - 1, *ptr_next = ptr + num;
        for (; ptr != begin - 1 + index; --ptr, --ptr_next) {
            ::new (ptr_next) Obj(std::move(*ptr));
        }
    }

    void copy_forward_n(size_type index, size_type num) {
        Obj * ptr = begin + index, *ptr_forw = begin + index - num;
        for (; ptr != cur; ++ptr, ++ptr_forw) {
            ::new (ptr_forw) Obj(std::move(*ptr));
        }
    }

    bool isMyPointer(const Obj *ptr) const {
        return ptr >= begin && ptr < end;
    }

    bool isMyPointer(const typename List<Obj>::iterator &it) {
        iterator *itp = dynamic_cast<iterator*>(&it);
        return isMyPointer(itp->ptr);
    }

    void updateIterator(Pointer<typename List<Obj>::iterator> &it, size_type curCount, size_type count, Obj *obj) {
        iterator *pit = dynamic_cast<iterator*>(it.operator->());
        pit->setCurCount(curCount);
        pit->setCount(count);
        pit->setPtr(obj);
    }

public:
    class iterator : public List<Obj>::iterator {
        Obj *ptr;

    public:
        ~iterator() = default;

        iterator(Obj *ptr, size_type count, size_type index = 0) : List<Obj>::iterator(count, index), ptr(ptr) {}

        Obj &next() override {
            Obj &obj = *ptr;
            ++ptr;
            ++List<Obj>::iterator::curCount;
            return obj;
        }

        void setPtr(Obj *p) {
            ptr = p;
        }
    };

    Reference<typename List<Obj>::iterator> getBeginIterator() override {
        iterator *pit = new iterator(begin, size());
        return Reference<typename List<Obj>::iterator>(pit);
    }

    // constructors
    explicit Vector(size_type nsize = 1) {
        if (nsize == 0) {
            nsize = 1;
        }
        allocate_new_size(nsize);
        cur = begin;
    }

    explicit Vector(Obj * pobj, size_type nsize = 1) {
        if (nsize == 0) {
            nsize = 1;
        }
        allocate_new_size(nsize);
        cur = end;
        for (size_type i = 0; i < nsize; ++i) {
            // Obj must override copy constructor and operator
            ::new (&begin[i]) Obj(*pobj);
        }
    }

    explicit Vector(const Obj &robj, size_type nsize = 1) {
        if (nsize == 0) {
            nsize = 1;
        }
        allocate_new_size(nsize);
        cur = end;
        for (size_type i = 0; i < nsize; ++i) {
            ::new (&begin[i]) Obj(robj); // Obj must override copy constructor and operator
        }
    }

    explicit Vector(Obj && rrobj, size_type nsize = 1) {
        if (nsize == 0) {
            nsize = 1;
        }
        allocate_new_size(nsize);
        cur = end;
        for (size_type i = 0; i < nsize; ++i) {
            ::new (&begin[i]) Obj(std::forward<Obj>(rrobj));  // Obj must override copy constructor and operator
        }
    }

    Vector(const Vector &rhs) {
        size_type nsize = rhs.size();
        allocate_new_size(nsize);
        copy_mem_move(rhs.begin, begin, nsize);
    }

    Vector(Vector &&rhs) noexcept {
        Obj * p = Allocator::allocate<Obj>(1);
        begin = rhs.begin;
        cur = rhs.cur;
        end = rhs.end;
        rhs.begin = p;
        rhs.end = p + 1;
        rhs.cur = p;
    }

    Vector<Obj> &operator=(const Vector<Obj> &rhs) {
        if (&rhs == this) {
            return *this;
        }
        size_type nsize = rhs.size();
        Allocator::deallocate(begin, nsize);
        begin = Allocator::allocate<Obj>(nsize);
        end = begin + nsize;
        cur = end;
        for (size_type i = 0; i < nsize; ++i) {
            new (&begin[i]) Obj(rhs.begin[i]);
        }
        return *this;
    }

    Vector<Obj> &operator=(Vector<Obj> &&rhs) noexcept {
        if (&rhs == this) {
            return *this;
        }
        Allocator::deallocate(begin, capacity());
        begin = rhs.begin;
        end = rhs.end;
        cur = rhs.cur;
        rhs.begin = Allocator::allocate<Obj>();
        rhs.end = rhs.begin + 1;
        rhs.cur = rhs.begin;
        return *this;
    }

    virtual ~Vector() {
        Allocator::deallocate(begin, capacity());
    }

    void resize(size_type nsize) {
        Obj *newspace = Allocator::allocate<Obj>(nsize);
        for (Obj *p = newspace, *b = begin; p - newspace < nsize; ++p) {
            ::new (p) Obj(std::move(*b));
        }
        clear();
        begin = newspace;
        end = newspace + nsize;
        cur = end;
    }

    void clear() override {
        Allocator::deallocate(begin, capacity());
        begin = Allocator::allocate<Obj>();
        end = begin + 1;
        cur = begin;
    }

    size_type size() const override {
        return cur - begin;
    }

    size_type capacity() const override {
        return end - begin;
    }

    // operations
    void add(const Obj & robj) override {
        if (end == cur) {
            expand();
        }
        ::new (cur) Obj(robj);
        ++cur;
    }

    void add(Obj && rrobj) override {
        if (end == cur) {
            expand();
        }
        ::new (cur) Obj(std::forward<Obj>(rrobj));
        ++cur;
    }

    void add(size_type index, const Obj &obj) override {
        if (index > size()) {
            throw IndexOutOfRangeException();
        }
        if (end == cur) {
            expand();
        }
        copy_back_n(index, 1);
        ::new (&begin[index]) Obj(obj);
        ++cur;
    }

    void add(size_type index, Obj &&obj) override {
        if (index > size()) {
            throw IndexOutOfRangeException();
        }
        if (end == cur) {
            expand();
        }
        if (index < size()) {
            copy_back_n(index, 1);
        }
        ::new (&begin[index]) Obj(std::forward<Obj>(obj));
        ++cur;
    }

    void addFirst(const Obj &obj) override {
        add(0, obj);
    }

    void addFirst(Obj &&obj) override {
        add(0, std::forward<Obj>(obj));
    }

    Obj pollLast() override {
        if (size() == 0) {
            throw EmptyContainerException();
        }
        --cur;
        Obj ret(std::move(*cur));
        return std::move(ret);
    }

    Obj pollFirst() override {
        if (size() == 0) {
            throw EmptyContainerException();
        }
        Obj ret(std::move(*begin));
        ++begin;
        copy_forward_n(1, 1);
        return std::move(ret);
    }

    Obj & getFirst() override {
        if (size() == 0) {
            throw EmptyContainerException();
        }
        return *begin;
    }

    Obj & getLast() override {
        if (size() == 0) {
            throw EmptyContainerException();
        }
        return cur[-1];
    }

    Obj & operator[](size_type index) override {
        if (index >= size()) {
            throw IndexOutOfRangeException();
        }
        return begin[index];
    }

    void swap(size_type index1, size_type index2) {
        Obj t = std::move(begin[index1]);
        begin[index1] = std::move(begin[index2]);
        begin[index2] = std::move(t);
    }

    void remove(size_type index) override {
        if (index >= size()) {
            throw IndexOutOfRangeException();
        }
        if (index == 0) {
            pollFirst();
            return;
        }
        copy_forward_n(index + 1, 1);
        --cur;
    }

    void remove(const Obj &obj) override {
        size_type index = indexOf(obj);
        remove(index);
    }

    void remove(Pointer<typename List<Obj>::iterator> &it) override {
        iterator *pit = dynamic_cast<iterator*>(it.operator->());
        size_type index = pit->getIndex();
        remove(index);
        updateIterator(it, index, size(), &begin[index]);
    }

    void removeAll(List<Obj> &rhs) override {

    }

    void addAll(List<Obj> &rhs) {
        addAll(size(), rhs);
    }

    void addAll(List<Obj> &&rhs) {
        addAll(size(), std::forward<List<Obj>>(rhs));
    }

    void addAll(size_type index, const Vector<Obj> &rhs) {
        if (index > size()) {
            throw IndexOutOfRangeException();
        }
        size_type newsize = rhs.size() + size();
        // no sufficient current space
        if (capacity() < newsize) {  // find new space
            Obj *newspace = Allocator::allocate<Obj>(newsize << 1);
            copy_mem_dup(begin, newspace, index);
            copy_mem_dup(rhs.begin, newspace + index, rhs.size());
            copy_mem_dup(begin + index + 1,
                          newspace + index + rhs.size(),
                          size() - index);
            begin = newspace;
            cur = newspace + newsize;
            end = cur + newsize;
            return;
        }
        // sufficient current space
        // copy back
        copy_back_n(index, rhs.size());
        copy_mem_dup(rhs.begin, begin + index, rhs.size());
        cur += rhs.size();
    }

    void addAll(size_type index, Vector<Obj> &&rhs) {
        if (index > size()) {
            throw IndexOutOfRangeException();
        }

        size_type newsize = rhs.size() + size();
        // no sufficient current space
        if (capacity() < newsize) {  // find new space
            Obj *newspace = Allocator::allocate<Obj>(newsize << 1);
            copy_mem_move(begin, newspace, index);
            copy_mem_move(rhs.begin, newspace + index, rhs.size());
            copy_mem_move(begin + index + 1,
                         newspace + index + rhs.size(),
                         size() - index);
            begin = newspace;
            cur = newspace + newsize;
            end = cur + newsize;
            rhs.clear();
            return;
        }
        // sufficient current space
        // copy back
        copy_back_n(index, rhs.size());
        copy_mem_move(rhs.begin, begin + index, rhs.size());
        cur += rhs.size();
        rhs.clear();
    }

    void addAll(size_type index, List<Obj> &rhs) override {
        if (index > size()) {
            throw IndexOutOfRangeException();
        }
        size_type newsize = rhs.size() + size();
        // no sufficient space
        if (capacity() < newsize) {
            Obj *newspace = Allocator::allocate<Obj>(newsize << 1);
            copy_mem_dup(begin, newspace, index);
            size_type ii = index;
            auto it = rhs.getBeginIterator();
            while (it->hasNext()) {
                Obj &p = it->next();
                ::new (newspace + ii) Obj(p);
                ++ii;
            }
            copy_mem_dup(begin + index + 1,
                          newspace + index + rhs.size(),
                          size() - index);
            begin = newspace;
            cur = newspace + newsize;
            end = cur + newsize;
            return;
        }
        // sufficient space
        copy_back_n(index, rhs.size());
        size_type ii = index;
        auto it = rhs.getBeginIterator();
        while (it->hasNext()) {
            Obj &p = it->next();
            ::new (begin + ii) Obj(p);
            ++ii;
        }
        cur += rhs.size();
        rhs.clear();
    }

    void addAll(size_type index, List<Obj> &&rhs) {
        if (index > size()) {
            throw IndexOutOfRangeException();
        }
        size_type newsize = rhs.size() + size();
        // no sufficient space
        if (capacity() < newsize) {
            Obj *newspace = Allocator::allocate<Obj>(newsize << 1);
            copy_mem_move(begin, newspace, index);
            size_type ii = index;
            auto it = rhs.getBeginIterator();
            while (it->hasNext()) {
                Obj &p = it->next();
                ::new (begin + ii) Obj(std::move(p));
                ++ii;
            }
            copy_mem_move(begin + index + 1,
                          newspace + index + rhs.size(),
                          size() - index);
            begin = newspace;
            cur = newspace + newsize;
            end = cur + newsize;
            return;
        }
        // sufficient space
        copy_back_n(index, rhs.size());
        size_type ii = index;
        auto it = rhs.getBeginIterator();
        while (it->hasNext()) {
            Obj &p = it->next();
            ::new (begin + ii) Obj(std::move(p));
            ++ii;
        }
        cur += rhs.size();
        rhs.clear();
    }

    void addBefore(Pointer<typename List<Obj>::iterator> &it, const Obj &obj) override {
        size_type index = it->getIndex();
        add(index, obj);
        ++index;
        updateIterator(it, index, size(), &begin[index]);
    }

    void addBefore(Pointer<typename List<Obj>::iterator> &it, Obj &&obj) override {
        size_type index = it->getIndex();
        add(index, std::forward<Obj>(obj));
        ++index;
        updateIterator(it, index, size(), &begin[index]);
    }

    void addAfter(Pointer<typename List<Obj>::iterator> &it, const Obj &obj) override {
        size_type index = it->getIndex() + 1;
        add(index, obj);
        updateIterator(it, index, size(), &begin[index]);
    }

    void addAfter(Pointer<typename List<Obj>::iterator> &it, Obj &&obj) override {
        size_type index = it->getIndex() + 1;
        add(index, std::forward<Obj>(obj));
        updateIterator(it, index, size(), &begin[index]);
    }

    void addAllBefore(Pointer<typename List<Obj>::iterator> &it, List<Obj> &rhs) override {
        size_type index = it->getIndex();
        addAll(index, rhs);
        index += rhs.size();
        updateIterator(it, index, size(), &begin[index]);
    }

    void addAllBefore(Pointer<typename List<Obj>::iterator> &it, List<Obj> &&rhs) override {
        size_type index = it->getIndex();
        addAll(index, std::forward<List<Obj>>(rhs));
        index += rhs.size();
        updateIterator(it, index, size(), &begin[index]);
    }

    void addAllAfter(Pointer<typename List<Obj>::iterator> &it, List<Obj> &rhs) override {
        size_type index = it->getIndex();
        addAll(index + 1, rhs);
        updateIterator(it, index, size(), &begin[index]);
    }

    void addAllAfter(Pointer<typename List<Obj>::iterator> &it, List<Obj> &&rhs) override {
        size_type index = it->getIndex();
        addAll(index + 1, std::forward<List<Obj>>(rhs));
        updateIterator(it, index, size(), &begin[index]);
    }

    size_type indexOf(const Obj &obj) const override {
        Obj *p = begin;
        while (p != cur) {
            if (*p == obj) {
                return p - begin;
            }
            ++p;
        }
        return size();  // not found
    }

    size_type lastIndexOf(const Obj &obj) const override {
        Obj *p = cur - 1;
        while (p != begin - 1) {
            if (*p == obj) {
                return p - begin;
            }
            --p;
        }
        return size();  // not found
    }

    bool contains(const Obj &obj) override {
        return indexOf(obj) < size();
    }

    bool containsAll(List<Obj> &rhs) override {
        Set<Obj> &&set = toHashSet();
        auto it = rhs.getBeginIterator();
        while(it->hasNext()) {
            Obj &obj = it->next();
            if (!set.contains(obj)) {
                return false;
            }
        }
        return true;
    }

    HashSet<Obj> toHashSet() {
        HashSet<Obj> res;
        auto it = getBeginIterator();
        while(it->hasNext()) {
            Obj &obj = it->next();
            res.put(obj);
        }
        return std::move(res);
    }
};


#endif //MYSTL_VECTOR_HPP
