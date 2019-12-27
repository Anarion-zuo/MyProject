//
// Created by anarion on 2019/11/7.
//

#ifndef MYSTL_NON_FUNCTOR_HPP
#define MYSTL_NON_FUNCTOR_HPP


#include "functor.hpp"

template <class Ret>
struct non_functor {
    virtual Ret operator() () = 0;
};


#endif //MYSTL_NON_FUNCTOR_HPP
