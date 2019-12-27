//
// Created by 左钰 on 2019/12/12.
//

#ifndef MYCPPLIB_MUTEX_H
#define MYCPPLIB_MUTEX_H

#include <pthread.h>
class Mutex {
    friend class CondVar;
protected:
    pthread_mutex_t mutex;
public:
    Mutex();
    virtual ~Mutex();

    void lock();
    void release();
    bool tryLock();
    bool isLocked();
};


#endif //MYCPPLIB_MUTEX_H
