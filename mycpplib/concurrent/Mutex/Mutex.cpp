//
// Created by 左钰 on 2019/12/12.
//

#include "Mutex.h"

Mutex::Mutex() {
    int ret;
    ret = pthread_mutex_init(&mutex, nullptr);
}

Mutex::~Mutex() {
    pthread_mutex_destroy(&mutex);
}

void Mutex::lock() {
    pthread_mutex_lock(&mutex);
}

void Mutex::release() {
    pthread_mutex_unlock(&mutex);
}

bool Mutex::tryLock() {
    return !pthread_mutex_trylock(&mutex);
}

bool Mutex::isLocked() {
    bool ret = tryLock();
    if (ret) {
        release();
    }
    return ret;
}
