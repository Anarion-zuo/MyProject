//
// Created by 左钰 on 2019/12/13.
//

#ifndef MYCPPLIB_BINDED_HPP
#define MYCPPLIB_BINDED_HPP


#include <tuple>
#include "Callable.h"

template <typename func, typename ...Args>
class Binded : public Callable {
    func f;
    std::tuple<Args...> args;
public:
    explicit Binded(func f, Args ...args) : f(f), args(args...) {}

    void run() override {
        f(args);
    }
};

template <typename func, typename ...Args>
Binded<func, Args...> bind(func f, Args ...args) {
    return Binded<func, Args...>(f, args...);
}


#endif //MYCPPLIB_BINDED_HPP
