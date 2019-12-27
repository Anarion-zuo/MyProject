//
// Created by 左钰 on 2019/12/12.
//

#include "CondVar.h"

void CondVar::signal() {
    pthread_cond_signal(&cond);
}

void CondVar::wait() {
    mutex.lock();
    while(predicator->operator()()) {
        pthread_cond_wait(&cond, &mutex.mutex);
    }
}

void CondVar::signalAll() {
    pthread_cond_broadcast(&cond);
}

void CondVar::setPredicator(non_functor<bool> *pred) {
    predicator = pred;
}
