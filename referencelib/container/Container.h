//
// Created by anarion on 2019/12/29.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_CONTAINER_H
#define REFERENCELIB_CONTAINER_H

#include "../base/Pointer.hpp"
#include "SString.h"

template <typename T = Object>
class Container : public Object {
public:
    virtual void remove(Pointer<T> p) = 0;
    virtual void removeAll(Pointer<Container<T>> rhs) = 0;

    virtual void clear() = 0;
    virtual size_type size() const = 0;

    class iterator {
    protected:
        size_type index, size;
    public:
        explicit iterator(size_type size, size_type index = 0) : index(index), size(size) {}

        virtual Pointer<T> next() = 0;
        virtual bool hasNext() const {
            return index < size;
        }
    };

    virtual Pointer<iterator> getBeginIterator() = 0;

    typedef typename Container<T>::iterator parent_iterator;

    Pointer<SString> toString() override {
        Pointer<SString> str = new SString;
        char leftbracket = '[', righbracket = ']';
        str->append(&leftbracket, 1);
        auto it = (getBeginIterator());
        while (it->hasNext()) {
            Pointer<SString> s = it->next()->toString();
            str->append(s);
            s.release();
            char __t = ',';
            str->append(&__t, 1);
        }
        str->append(&righbracket, 1);
        return str;
    }
};


#endif //REFERENCELIB_CONTAINER_H
