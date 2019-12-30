//
// Created by 左钰 on 2019/12/29.
//

#ifndef REFERENCELIB_CALLABLE_H
#define REFERENCELIB_CALLABLE_H


#include "../base/Object.h"

template <typename Ret>
class Callable : public Object {
public:
    virtual void run() = 0;
    virtual Ret getReturn() {

    }
};


#endif //REFERENCELIB_CALLABLE_H
