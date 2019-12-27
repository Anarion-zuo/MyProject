//
// Created by 左钰 on 2019/12/12.
//

#ifndef MYCPPLIB_CONDVAR_H
#define MYCPPLIB_CONDVAR_H

#include <pthread.h>
#include <concurrent/Mutex/Mutex.h>
#include <functors/non_functor.hpp>
#include <allocator/Allocator.hpp>

class CondVar {
protected:
    pthread_cond_t cond;
    Mutex &mutex;
    non_functor<bool> *predicator;
public:
    explicit CondVar(Mutex &mutex, non_functor<bool>* pred) : mutex(mutex), predicator(pred) {
        pthread_cond_init(&cond, nullptr);
    }

    ~CondVar() {
        pthread_cond_destroy(&cond);
    }

    void setPredicator(non_functor<bool> *pred);

    void wait();
    void signal();
    void signalAll();
};


#endif //MYCPPLIB_CONDVAR_H
