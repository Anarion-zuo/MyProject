//
// Created by 左钰 on 2019/12/29.
//

#ifndef REFERENCELIB_QUEUE_HPP
#define REFERENCELIB_QUEUE_HPP


#include "../base/Object.h"

template <typename T>
class Queue : public Object {
public:
    virtual void put(Pointer<T> ptr) = 0;
    virtual Pointer<T> poll() = 0;
    virtual bool isEmpty() const = 0;
};


#endif //REFERENCELIB_QUEUE_HPP
