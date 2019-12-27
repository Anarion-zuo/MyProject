//
// Created by 左钰 on 2019/12/12.
//

#ifndef MYCPPLIB_THREAD_H
#define MYCPPLIB_THREAD_H

#include <pthread.h>
#include "Callable.h"

class Thread : public Callable {
    friend class ThreadPool;
protected:
    pthread_t pid;

    static void *startRoutine(void *pVoid);
public:

    void start();

    void run() override {

    }

    void join();

    bool isRunning();
};


#endif //MYCPPLIB_THREAD_H
