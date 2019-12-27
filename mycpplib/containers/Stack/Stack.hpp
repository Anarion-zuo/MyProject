//
// Created by 左钰 on 2019/12/12.
//

#ifndef MYCPPLIB_STACK_HPP
#define MYCPPLIB_STACK_HPP


#include <containers/ContainerInterface.hpp>

template <typename Obj>
class Stack : public ContainerInterface<Obj> {
public:
    virtual void put(const Obj &obj) = 0;
    virtual void put(Obj &obj) = 0;
    virtual Obj poll() = 0;
};


#endif //MYCPPLIB_STACK_HPP
