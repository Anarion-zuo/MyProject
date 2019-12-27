//
// Created by 左钰 on 2019/12/12.
//

#include <cerrno>
#include <signal.h>
#include "Thread.h"

void Thread::join() {
    int ret;
    ret = pthread_join(pid, nullptr);
}

void Thread::start() {
    int ret;
    ret = pthread_create(&pid, nullptr, startRoutine, reinterpret_cast<void*>(this));
}

void *Thread::startRoutine(void *pVoid) {
    auto *_this = reinterpret_cast<Thread*>(pVoid);
    _this->run();
    return nullptr;
}

bool Thread::isRunning() {
    int ret = pthread_kill(pid, 0);
    return ret != ESRCH;
}
