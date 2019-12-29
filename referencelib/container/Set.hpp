//
// Created by 左钰 on 2019/12/29.
//

#ifndef REFERENCELIB_SET_HPP
#define REFERENCELIB_SET_HPP


#include "Container.h"

template <typename T>
class Set : public Container<T> {
public:
    virtual void put(Pointer<T> p) = 0;
    virtual void putAll(Pointer<Container<T>> rhs) = 0;

    virtual bool contains(Pointer<T> p) = 0;
    virtual bool containsAll(Pointer<Container<T>> rhs) {
        
    }
};


#endif //REFERENCELIB_SET_HPP
