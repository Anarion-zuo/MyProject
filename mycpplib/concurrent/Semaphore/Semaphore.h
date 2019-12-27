//
// Created by 左钰 on 2019/12/12.
//

#ifndef MYCPPLIB_SEMAPHORE_H
#define MYCPPLIB_SEMAPHORE_H

#include <semaphore.h>

class Semaphore {
protected:
    sem_t sem;
public:
    explicit Semaphore(unsigned int tNum);
    ~Semaphore();

    void wait();
    void tryWait();
    bool isLocked();
    void release();
};


#endif //MYCPPLIB_SEMAPHORE_H
