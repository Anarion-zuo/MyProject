//
// Created by 左钰 on 2019/12/29.
//

#ifndef REFERENCELIB_GARBAGECOLLECTOR_H
#define REFERENCELIB_GARBAGECOLLECTOR_H


#include "../container/List/LinkedList.hpp"
#include "../container/Queue/BlockQueue.hpp"

class GarbageCollector : public Object {
protected:
    struct Node {
//        LinkedList<Node*> nexts;
        Object *ptr;
        size_type scannedCount = 0;
        bool reached = false;

        explicit Node(Object *p = nullptr) : ptr(p) {}
    };

//    BlockQueue<Node> youngs, olds;
//    BlockQueue<Node> youngHeads, oldHeads;

    static Pointer<GarbageCollector> instance;
    GarbageCollector() = default;
public:
    static Pointer<GarbageCollector> getInstance();


};


#endif //REFERENCELIB_GARBAGECOLLECTOR_H
