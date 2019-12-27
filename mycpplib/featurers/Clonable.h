//
// Created by anarion on 2019/12/17.
//

#ifndef MYCPPLIB_CLONABLE_H
#define MYCPPLIB_CLONABLE_H


class Clonable {
public:
    virtual auto clone() -> decltype(*this) = 0;
};


#endif //MYCPPLIB_CLONABLE_H
