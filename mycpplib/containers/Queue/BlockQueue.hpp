//
// Created by 左钰 on 2019/12/12.
//

#ifndef MYCPPLIB_BLOCKQUEUE_HPP
#define MYCPPLIB_BLOCKQUEUE_HPP


#include <concurrent/Mutex/Mutex.h>
#include <concurrent/Semaphore/Semaphore.h>
#include <concurrent/CondVar/CondVar.h>
#include "ListQueue.hpp"

template <typename Obj>
class BlockQueue : public ListQueue<Obj> {
    struct __predicator : public non_functor<bool> {
        BlockQueue<Obj> *_this;
        explicit __predicator(BlockQueue<Obj> *_this = nullptr) : _this(_this) {}

        bool operator()() override {
            return _this->isEmpty();
        }
    };
protected:
    Mutex mutex;
    CondVar cond;
    __predicator predicator;
public:
    BlockQueue() : cond(mutex, nullptr) {
        predicator._this = this;
        cond.setPredicator(&predicator);
    }
    ~BlockQueue() = default;

    BlockQueue<Obj> &operator=(BlockQueue<Obj> &&rhs) noexcept {
        ListQueue<Obj>::operator=(std::forward<BlockQueue<Obj>>(rhs));
        return *this;
    }

    void put(const Obj &obj) override {
        mutex.lock();
        ListQueue<Obj>::put(obj);
        mutex.release();
        cond.signalAll();
    }

    void put(Obj &&obj) override {
        mutex.lock();
        ListQueue<Obj>::put(std::forward<Obj>(obj));
        mutex.release();
        cond.signalAll();
    }

    Obj poll() override {
        cond.wait();
        Obj obj = ListQueue<Obj>::poll();
        mutex.release();
        return std::move(obj);
    }
};


#endif //MYCPPLIB_BLOCKQUEUE_HPP
