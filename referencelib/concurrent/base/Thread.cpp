//
// Created by 左钰 on 2019/12/29.
//

#include "Thread.h"

Thread::Thread() {

}

void * Thread::runThis(void *p) {
    Thread *_this = reinterpret_cast<Thread *>(p);
    _this->run();
    return nullptr;
}

void Thread::start() {
    pthread_create(&tid, nullptr, runThis, this);
}
