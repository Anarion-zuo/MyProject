//
// Created by 左钰 on 2019/12/9.
//

#ifndef MYCPPLIB_UNMOVABLE_H
#define MYCPPLIB_UNMOVABLE_H


class UnMovable {
protected:
    UnMovable() = default;
public:
    ~UnMovable() = default;
    UnMovable(UnMovable &&) noexcept = delete;
    UnMovable &operator=(UnMovable &&) noexcept = delete;
};


#endif //MYCPPLIB_UNMOVABLE_H
