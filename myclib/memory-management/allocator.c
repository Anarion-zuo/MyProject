//
// Created by anarion on 2019/10/30.
//

#include <stdlib.h>
#include "allocator.h"
#include "../erronos.h"
#include <string.h>

struct head_ptr {   // 8 bytes
    struct head_ptr *next;
};

struct allocator {
    struct head_ptr *heads[16];
    size_t current_size;

    // pool
    void *begin, *end;
};

// set a global private allocator instance, all program uses this
static struct allocator allocator_instance = {
        .heads = {NULL},
        .current_size = 0,
        .begin = NULL,
        .end = NULL,
};

static struct allocator *allocator = &allocator_instance;

static size_t pool_size() {
    return (void *)allocator->end - (void *)allocator->begin;
}

static struct head_ptr * make_list(struct head_ptr *node, size_t index, size_t num) {
//    struct head_ptr ob;
    size_t step = (index + 1) << 3ul;
    // dont give 0 num, dont be dump
    for (size_t i = 0; i < num - 1; ++i) {
//        *node = ob;
        node->next = (void *)node + step;
        node = node->next;
    }
    node->next = NULL;
    return (void *)node + step;
}

int allocate(char **item, size_t size) {
    if (item == NULL) {
        return stat_nothing_done;
    }
    if (size == 0) {
        *item = NULL;
        return stat_noerr;
    }
    // too large requested
    if (size > 16ul << 3ul) {
        void *p = malloc(size);
        if (p == NULL) {
            *item = NULL;
            return stat_malloc_failed;
        }
        *item = p;
        return stat_noerr;
    }
    int ret;
    // round up sizes
    size_t index = size >> 3ul;   // serves as index for the heads
    size_t round_size = (index) << 3ul;
    if (round_size == size) {
        --index;
    } else {
        size = round_size + 8;
    }
    struct head_ptr **heads = allocator->heads;
    // head has more
    if (heads[index]) {
        *item = (char *) heads[index];
        heads[index] = heads[index]->next;
        allocator->current_size += size;
        return stat_noerr;
    }
    // enough pool
    size_t psize = pool_size();
    if (psize >= size) {
        heads[index] = allocator->begin;
        size_t more_num = psize / ((index + 1) << 3ul);
        if (more_num >= 20) {
            // give the pool to the head
            allocator->begin = make_list(heads[index], index, 20);
        } else {
            allocator->begin = make_list(heads[index], index, more_num);
        }
        *item = (char *) heads[index];
        heads[index] = heads[index]->next;
        allocator->current_size += size;
        return stat_noerr;
    }
    // not enough
    size_t pindex = psize >> 3ul;
    round_size = pindex << 3ul;
    if (round_size == psize) {
        --pindex;
    } else {
        psize = round_size + 8;
    }
    if (psize != 0) {
        struct head_ptr *phead = heads[pindex];
        heads[pindex] = allocator->begin;
        heads[pindex]->next = phead;
    }
    // compute new space size
    size_t new_size = size * 20;
    size_t roundup = allocator->current_size >> 3ul;
    roundup = ((roundup >> 3ul) << 3ul) + 8;
    new_size += roundup;
    // allocate new space
    struct head_ptr *new_space = malloc(new_size);
    if (new_space == NULL) {
        return stat_malloc_failed;
    }
    heads[index] = new_space;
    allocator->begin = make_list(new_space, index, 20);
    allocator->end = (void *)new_space + new_size;
    allocator->current_size += size;
    return allocate(item, size);
}

void deallocate(void *item, size_t size) {
    if (item == NULL || size == 0) {
        return;
    }
    // too large requested
    if (size > 16ul << 3ul) {
        free(item);
        return;
    }
    // round up sizes
    size_t index = size >> 3ul;   // serves as index for the heads
    size_t round_size = (index) << 3ul;
    if (round_size == size) {
        --index;
    } else {
        size = round_size + 8;
    }
    struct head_ptr **heads = allocator->heads;
    struct head_ptr *ptr = item, *old_head = heads[index];
    heads[index] = ptr;
    ptr->next = old_head;
}