//
// Created by anarion on 2019/10/30.
//

#ifndef MYCLIB_ALLOCATOR_H
#define MYCLIB_ALLOCATOR_H

#include <stdlib.h>

//int allocator_init(struct allocator *item);
int allocate(char **item, size_t size);
void deallocate(void *item, size_t size);

#endif //MYCLIB_ALLOCATOR_H
