//
// Created by anarion on 2019/10/31.
//

#ifndef MYCLIB_VECTOR_H
#define MYCLIB_VECTOR_H

#include "allocator.h"

struct vector {
    size_t it_size;
    char *begin, *end, *cur;
};

int vector_pushback(struct vector *vector, char *item);
int vector_init(struct vector *vector, size_t it_size, size_t init_size);


#endif //MYCLIB_VECTOR_H
