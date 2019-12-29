//
// Created by 左钰 on 2019/12/29.
//

#include "CondVar.h"

CondVar::CondVar(Pointer<Mutex> mutex, Pointer<Callable<bool>> pred) : mutex(mutex), predicator(pred) {
    pthread_cond_init(&cid, nullptr);
}

CondVar::~CondVar() {
    pthread_cond_destroy(&cid);
    predicator.release();
}

void CondVar::wait() {
    bool flag = false;
    mutex->lock();
    while (true) {
        predicator->run();
        flag = predicator->getReturn();
        if (flag) {
            break;
        }
        pthread_cond_wait(&cid, mutex->getMid());
    }
}

void CondVar::signal() {
    pthread_cond_signal(&cid);
    mutex->unlock();
}

void CondVar::signalAll() {
    pthread_cond_broadcast(&cid);
    mutex->unlock();
}
