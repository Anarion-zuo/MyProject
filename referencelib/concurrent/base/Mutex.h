//
// Created by 左钰 on 2019/12/29.
//

#ifndef REFERENCELIB_MUTEX_H
#define REFERENCELIB_MUTEX_H


#include <pthread.h>

class Mutex {
protected:
    pthread_mutex_t mid;
public:
    Mutex();
    ~Mutex();

    void lock();
    void unlock();

    pthread_mutex_t *getMid() ;
};


#endif //REFERENCELIB_MUTEX_H
