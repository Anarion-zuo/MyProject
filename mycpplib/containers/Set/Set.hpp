//
// Created by 左钰 on 2019/12/7.
//

#ifndef MYCPPLIB_SET_HPP
#define MYCPPLIB_SET_HPP

#include <base-classes/Object.h>
#include <functors/unary_functor.h>
#include <wrappers/Pointer/Pointer.hpp>
#include <containers/ContainerInterface.hpp>

template <typename Obj>
class Set : public ContainerInterface<Obj> {
public:
    typedef typename ContainerInterface<Obj>::iterator iterator;

    // insert
    virtual void put(const Obj &obj) = 0;
    virtual void put(Obj &&obj) = 0;
    virtual void putAll(ContainerInterface<Obj> &rhs) = 0;
    virtual void putAll(ContainerInterface<Obj> &&rhs) = 0;

    // remove
    virtual void remove(const Obj &obj) = 0;

    // contains
    virtual bool contains(const Obj &obj) = 0;
    virtual bool containsAll(ContainerInterface<Obj> &rhs) = 0;
};


#endif //MYCPPLIB_SET_HPP
