//
// Created by anarion on 2019/11/9.
//

#ifndef MYSTL_RVAL_HPP
#define MYSTL_RVAL_HPP

template <typename Obj>
Obj &&move(Obj &obj) {
    return static_cast<Obj&&>(obj);
}

#endif //MYSTL_RVAL_HPP
