//
// Created by anarion on 2019/12/17.
//

#ifndef MYCPPLIB_UNCONSTRUCTABLE_H
#define MYCPPLIB_UNCONSTRUCTABLE_H


struct UnConstructable {
protected:
    UnConstructable() = default;
    UnConstructable(const UnConstructable &rhs) = default;
    UnConstructable(UnConstructable &&rhs) = default;
    UnConstructable &operator=(const UnConstructable &rhs) = default;
    UnConstructable &operator=(UnConstructable &&rhs) = default;
};


#endif //MYCPPLIB_UNCONSTRUCTABLE_H
