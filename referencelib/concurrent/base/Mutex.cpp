//
// Created by 左钰 on 2019/12/29.
//

#include "Mutex.h"

Mutex::Mutex() {
    pthread_mutex_init(&mid, nullptr);
}

Mutex::~Mutex() {
    pthread_mutex_destroy(&mid);
}

void Mutex::lock() {
    pthread_mutex_lock(&mid);
}

void Mutex::unlock() {
    pthread_mutex_unlock(&mid);
}

pthread_mutex_t *Mutex::getMid() {
    return &mid;
}
