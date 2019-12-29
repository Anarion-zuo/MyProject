//
// Created by 左钰 on 2019/12/29.
//

#ifndef REFERENCELIB_CONDVAR_H
#define REFERENCELIB_CONDVAR_H

#include "Mutex.h"
#include "../../base/Pointer.hpp"
#include "../../callable/Callable.h"

class CondVar {
protected:
    pthread_cond_t cid;
    Pointer<Mutex> mutex;
    Pointer<Callable<bool>> predicator;
public:
    explicit CondVar(Pointer<Mutex> mutex, Pointer<Callable<bool>> pred);
    ~CondVar();

    void wait();
    void signal();
    void signalAll();
};


#endif //REFERENCELIB_CONDVAR_H
