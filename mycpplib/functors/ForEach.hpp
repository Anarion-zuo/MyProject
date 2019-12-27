//
// Created by 左钰 on 2019/12/5.
//

#ifndef MYCPPLIB_FOREACH_HPP
#define MYCPPLIB_FOREACH_HPP

#include "binary_functor.hpp"

typedef unsigned long size_type;

template <typename Ret, typename Obj>
struct ForEach : public binary_functor<Ret, Obj, size_type > {
    virtual Ret operator()(Obj &obj, size_type index) = 0;
};


#endif //MYCPPLIB_FOREACH_HPP
