//
// Created by 左钰 on 2019/12/12.
//

#include "ThreadPool.h"
#include <semaphore.h>

void ThreadPool::addIdleThread(size_type num) {
    for(size_type i = 0; i < num; ++i) {
        addIdleThread();
    }
}

void *ThreadPool::poolRoutine(void *p) {
    auto pinfo = Pointer<info>(reinterpret_cast<info*>(p));
    while(true) {
        pthread_mutex_lock(&pinfo->beginMutex);
        pthread_mutex_lock(&pinfo->joinMutex);
        Thread::startRoutine(pinfo->_this);
        pinfo->pool->workingSet.remove(pinfo);
        pinfo->pool->idleQueue.put(pinfo);
        pthread_mutex_unlock(&pinfo->joinMutex);
    }
    return nullptr;
}

void ThreadPool::addIdleThread() {
    auto pinfo = Pointer<info>(Allocator::allocate<info>());
    pthread_mutex_init(&pinfo->beginMutex, nullptr);
    pthread_mutex_lock(&pinfo->beginMutex);
    pthread_mutex_init(&pinfo->joinMutex, nullptr);
    pinfo->pool = this;
    pthread_create(&pinfo->pid, nullptr, poolRoutine, pinfo.getPointer());
    idleQueue.put(pinfo);
}

void ThreadPool::joinAll() {
    Pointer<info> pinfo;
    auto it = workingSet.getBeginIterator();
    while(it->hasNext()) {
        pinfo = it->next();
        pthread_mutex_lock(&pinfo->joinMutex);
        pthread_mutex_unlock(&pinfo->joinMutex);
    }
}

void ThreadPool::schedule(Thread &thread) {
    if (idleQueue.isEmpty()) {
        addIdleThread();
    }
    auto pinfo = idleQueue.poll();
    pinfo->_this = &thread;
    thread.pid = pinfo->pid;
    workingSet.put(pinfo);
    pthread_mutex_unlock(&pinfo->beginMutex);
}

ThreadPool::~ThreadPool() {
    joinAll();
    while(idleQueue.size()) {
        auto p = idleQueue.poll();
        p->_this->pid = -1;
        pthread_cancel(p->pid);
        Allocator::deallocate(p);
    }
}

size_type ThreadPool::idleCount() {
    return idleQueue.size();
}

size_type ThreadPool::workingCount() {
    return workingSet.size();
}
