//
// Created by 左钰 on 2019/12/29.
//

#include "GarbageCollector.h"

Pointer<GarbageCollector> GarbageCollector::instance = new GarbageCollector;

Pointer<GarbageCollector> GarbageCollector::getInstance() {
    return instance;
}
