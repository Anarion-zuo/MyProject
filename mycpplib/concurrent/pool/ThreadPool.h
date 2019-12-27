//
// Created by 左钰 on 2019/12/12.
//

#ifndef MYCPPLIB_THREADPOOL_H
#define MYCPPLIB_THREADPOOL_H


#include <containers/Queue/BlockQueue.hpp>
#include <concurrent/Callable/Thread.h>
#include <containers/Set/HashSet.hpp>


class ThreadPool {
protected:
    typedef void *(*routine_t)(void *);

    struct info : public Hashable {
        pthread_t pid;
        Thread *_this;
        pthread_mutex_t joinMutex, beginMutex;
        ThreadPool *pool;

        ~info() {
            pthread_mutex_destroy(&joinMutex);
            pthread_mutex_destroy(&beginMutex);
        }
    };

    BlockQueue<Pointer<info>> idleQueue;
    HashSet<Pointer<info>> workingSet;

    void addIdleThread();
    void addIdleThread(size_type num);

    static void *poolRoutine(void *info);
public:
    explicit ThreadPool(size_type size) {
        addIdleThread(size);
    }

    ~ThreadPool();

    size_type workingCount();
    size_type idleCount();

    void joinAll();
    void schedule(Thread &thread);
};


#endif //MYCPPLIB_THREADPOOL_H
