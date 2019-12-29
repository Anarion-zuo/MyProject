//
// Created by anarion on 2019/12/29.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_VECTOR_HPP
#define REFERENCELIB_VECTOR_HPP

#include "../List.h"
#include <cstring>

template <typename T>
class Vector : public List<T> {
protected:
    T **begin = nullptr, **cur = nullptr, **end = nullptr;

    void expand() {
        if (begin == nullptr) {
            begin = new T*[20];
            cur = begin;
            end = begin + 20;
            return;
        }
        size_type oldsize = capacity(), newsize = oldsize << 1ul, curoff = size();
        auto newspace = new T*[newsize];
        memcpy(newspace, begin, oldsize << 3ul);   // compute pointer size 8 bytes
        delete[] begin;
        begin = newspace;
        end = begin + oldsize;
        cur = begin + curoff;
    }

    void squeeze() {
        // TODO reduce size when lower than 1/3
    }

    void copy_back_1(size_type index) {
        memcpy(&begin[index], &begin[index + 1], size() - index);
        --cur;
        if (size() << 1ul < capacity() - size()) {
            squeeze();
        }
    }

    void copy_forward_1(size_type index) {
        if (cur == end) {
            expand();
        }
        memcpy(&begin[index + 1], &begin[index], size() - index);
        ++cur;
    }

    typedef typename Container<T>::iterator parent_iterator;
public:
    class iterator : public parent_iterator {
        T **p;
    public:
        explicit iterator(size_type size, T **p) : parent_iterator(size), p(p) {}

        Pointer<T> next() override {
            T **pp = p;
            ++parent_iterator::index;
            ++p;
            return *pp;
        }
    };

    Pointer<parent_iterator> getBeginIterator() override {
        return new iterator(size(), begin);
    }

    Vector() = default;

    explicit Vector(size_type num) : begin(new T*[num]), cur(begin), end(begin + num) {}

    ~Vector() {
        delete[] begin;
    }

    void clear() override {
        delete[] begin;
        begin = nullptr;
        end = nullptr;
        cur = nullptr;
    }

//    Pointer<Object> clone() override {
//        Pointer<Vector> p = new Vector();
//        p->begin = new T*[capacity()];
//        p->cur = p->begin + size();
//        p->end = p->begin + capacity();
//        memcpy(p->begin, begin, size());
//        return p;
//    }

    void add(Pointer<T> p) override {
        if (cur == end) {
            expand();
        }
        *cur = p.operator->();
        ++cur;
    }

    void addFirst(Pointer<T> p) override {
        add(p, 0);
    }

    void addAll(Pointer<Container<T>> rhs) override {

    }

    void remove(Pointer<T> p) override {
        for (size_type i = 0; i < size(); ++i) {
            if (begin[i] == p.operator->()) {
                copy_back_1(i);
            }
        }
    }

    void removeAll(Pointer<Container<T>> rhs) override {

    }

    void add(Pointer<T> p, size_type index) override {
        copy_forward_1(index);
        begin[index] = p.operator->();
    }

    Pointer<T> get(size_type index) override {
        if (index > size()) {

        }
        return begin[index];
    }

    Pointer<T> poll() override {
        T *p = cur[-1];
        --cur;
        return p;
    }

    size_type size() const override {
        return cur - begin;
    }

    size_type capacity() const {
        return end - begin;
    }

    size_type indexOf(Pointer<Object> p) override {
        for (size_type i = 0; i < size(); ++i) {
            if (p->equals(begin[i])) {
                return i;
            }
        }
        return size();
    }

};


#endif //REFERENCELIB_VECTOR_HPP
