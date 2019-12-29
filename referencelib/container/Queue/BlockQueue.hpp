//
// Created by 左钰 on 2019/12/29.
//

#ifndef REFERENCELIB_BLOCKQUEUE_HPP
#define REFERENCELIB_BLOCKQUEUE_HPP


#include "../../concurrent/base/Mutex.h"
#include "../../concurrent/base/CondVar.h"
#include "ListQueue.h"

template <typename T>
class BlockQueue : public ListQueue<T> {
    class __pred_empty : public Callable<bool> {
        BlockQueue<T> *_this;
        bool flag;
    public:
        explicit __pred_empty(BlockQueue<T> *p) : _this(p) {}
        void run() override {
            flag = !_this->isEmpty();
        }
        bool getReturn() override {
            return flag;
        }
    };
protected:
    Pointer<Mutex> mutex;
    Pointer<CondVar> cond;
public:
    BlockQueue() : mutex(new Mutex) {
        cond = new CondVar(mutex, new __pred_empty(this));
    }
    ~BlockQueue() {
        mutex.release();
        cond.release();
    }

    void put(T *ptr) {
        mutex->lock();
        ListQueue<T>::put(ptr);
        mutex->unlock();
    }

    Pointer<T> poll() {
        cond->wait();
        Pointer<T> p = ListQueue<T>::poll();
        cond->signalAll();
        return p;
    }
};


#endif //REFERENCELIB_BLOCKQUEUE_HPP
