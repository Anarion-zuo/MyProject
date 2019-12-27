//
// Created by anarion on 2019/11/27.
//

#ifndef MYCPPLIB_OBJECT_H
#define MYCPPLIB_OBJECT_H
typedef unsigned long size_type;

class SString;
class Object {
protected:

    Object() {

    }
public:
    typedef unsigned long hash_t;

    virtual SString toString() const;
//    virtual hash_t hash() const ;

};


#endif //MYCPPLIB_OBJECT_H
