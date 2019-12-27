//
// Created by 左钰 on 2019/12/12.
//

#include "Semaphore.h"

Semaphore::Semaphore(unsigned int tNum) {
    sem_init(&sem, 0, tNum);
}

Semaphore::~Semaphore() {
    sem_destroy(&sem);
}

void Semaphore::wait() {
    sem_wait(&sem);
}

void Semaphore::tryWait() {
    sem_trywait(&sem);
}

bool Semaphore::isLocked() {
    bool ret = !sem_trywait(&sem);
    if (ret) {
        release();
    }
    return ret;
}

void Semaphore::release() {
    sem_post(&sem);
}
