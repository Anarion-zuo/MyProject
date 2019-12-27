//
// Created by 左钰 on 2019/12/12.
//

#ifndef MYCPPLIB_PRIORITYQUEUE_HPP
#define MYCPPLIB_PRIORITYQUEUE_HPP

#include <containers/List/Vector.hpp>
#include "Queue.hpp"

template <typename Obj>
class PriorityQueue : public Queue<Obj> {
protected:
    Vector<Obj> arr;

    static size_type getLeftChild(size_type index) {
        return (index << 1ul) + 1;
    }

    static size_type getRightChild(size_type index) {
        return (index << 1ul) + 2;
    }

    static size_type getParent(size_type index) {
        return index >> 1ul;
    }

    void heapifyAdd() {
        size_type cur = arr.size() - 1, parent = getParent(cur);
        while(arr[parent] < arr[cur] && cur) {
            arr.swap(parent, cur);
            cur = parent;
            parent = getParent(cur);
        }
    }

    void heapifyPop() {
        size_type cur = 0, left = getLeftChild(cur), right = getRightChild(cur);
        while (arr[left] < arr[cur] && arr[right] < arr[cur]) {
            if (arr[left] > arr[right]) {
                arr.swap(cur, left);
                cur = left;
            } else {
                arr.swap(cur, right);
                cur = right;
            }
            left = getLeftChild(cur);
            right = getRightChild(cur);
        }

    }

public:
    unsigned long size() const override {
        return arr.size();
    }

    unsigned long capacity() const override {
        return arr.capacity();
    }

    void clear() override {
        arr.clear();
    }

    void put(const Obj &obj) override {
        arr.add(obj);
        heapifyAdd();
    }

    void put(Obj &&obj) override {
        arr.add(std::forward<Obj>(obj));
        heapifyAdd();
    }

    Obj poll() override {
        arr.swap(0, arr.size() - 1);
        Obj obj = arr.pollLast();
        heapifyPop();
        return std::move(obj);
    }
};


#endif //MYCPPLIB_PRIORITYQUEUE_HPP
