//
// Created by 左钰 on 2019/12/29.
//

#ifndef REFERENCELIB_THREAD_H
#define REFERENCELIB_THREAD_H


#include <pthread.h>
#include "../../callable/Callable.h"

class Thread : public Callable<int> {
protected:
    pthread_t tid;

    static void * runThis(void *p);
public:
    Thread();

    void start();
};


#endif //REFERENCELIB_THREAD_H
