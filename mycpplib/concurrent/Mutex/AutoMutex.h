//
// Created by 左钰 on 2019/12/12.
//

#ifndef MYCPPLIB_AUTOMUTEX_H
#define MYCPPLIB_AUTOMUTEX_H


#include "Mutex.h"

class AutoMutex : public Mutex {
public:
    ~AutoMutex();
};


#endif //MYCPPLIB_AUTOMUTEX_H
