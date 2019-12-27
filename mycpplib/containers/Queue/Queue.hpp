//
// Created by 左钰 on 2019/12/10.
//

#ifndef MYCPPLIB_QUEUE_HPP
#define MYCPPLIB_QUEUE_HPP

#include <containers/ContainerInterface.hpp>

template <typename Obj>
class Queue {
public:
    virtual void put(const Obj &obj) = 0;
    virtual void put(Obj &&obj) = 0;
    virtual Obj poll() = 0;
    virtual size_type size() const = 0;
    virtual size_type capacity() const = 0;
    virtual void clear() = 0;
    virtual bool isEmpty() const = 0;
};


#endif //MYCPPLIB_QUEUE_HPP
