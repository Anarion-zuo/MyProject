//
// Created by anarion on 2019/11/8.
//

#ifndef MYSTL_UNCOPYABLE_H
#define MYSTL_UNCOPYABLE_H


class UnCopiable {
protected:
    UnCopiable() = default;
public:
    ~UnCopiable() = default;
    UnCopiable(const UnCopiable &) = delete;
    UnCopiable &operator=(const UnCopiable &) = delete;
};


#endif //MYSTL_UNCOPYABLE_H
