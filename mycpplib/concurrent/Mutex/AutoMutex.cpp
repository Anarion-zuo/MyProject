//
// Created by 左钰 on 2019/12/12.
//

#include "AutoMutex.h"

AutoMutex::~AutoMutex() {
    release();
    pthread_mutex_destroy(&mutex);
}
