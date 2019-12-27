//
// Created by anarion on 2019/10/31.
//

#include "vector.h"
#include "../erronos.h"



int vector_init(struct vector *vector, size_t it_size, size_t init_size) {
    if (it_size == 0 || vector == NULL) {
        return stat_nothing_done;
    }
    int ret;
    size_t nsize = it_size * init_size;
    vector->it_size = it_size;
    ret = allocate(&vector->begin, nsize);
    if (ret != stat_noerr) {
        return ret;
    }
    vector->end = vector->begin + nsize;
    vector->cur = vector->begin;
    return stat_noerr;
}

int vector_front(struct vector *vector, char *item) {
    if (vector == NULL || item == NULL) {
        return stat_nothing_done;
    }
    for (size_t i = 0; i < vector->it_size; ++i) {
        item[i] = vector->begin[i];
    }
    return stat_noerr;
}

int vector_back(struct vector *vector, char *item) {
    if (vector == NULL || item == NULL) {
        return stat_nothing_done;
    }
    for (size_t i = 0; i < vector->it_size; ++i) {
        item[i] = (vector->end - vector->it_size)[i];
    }
    return stat_noerr;
}

static int vector_is_full(struct vector *vector) {
    return vector->end == vector->cur;
}

static int vector_is_empty(struct vector *vector) {
    return vector->cur == vector->begin;
}

size_t vector_size(struct vector *vector) {
    return (vector->cur - vector->begin);
}

static int vector_expand(struct vector *vector) {
    char *old_begin = vector->begin,
    *old_end = vector->end, *new_begin;
    int ret;
    size_t old_size = vector_size(vector);
    ret = allocate(&new_begin, old_size << 1ul);
    if (ret != stat_noerr) {
        return ret;
    }
    char *new_block = new_begin;
    if (old_begin) {
        for (; old_begin != old_end;
               ++old_begin, ++new_block) {
            *new_block = *old_begin;
        }
    }
    vector->begin = new_begin;
    vector->cur = new_block;
    vector->end = new_block + old_size;
    return stat_noerr;
}

void vector_move(struct vector *src, struct vector *dst) {
    if (src == NULL || dst == NULL) {
        return;
    }
    deallocate(dst->begin, vector_size(dst));
    dst->begin = src->begin;
    dst->it_size = src->it_size;
    dst->cur = src->cur;
    dst->end = src->end;
    src->begin = NULL;
    src->cur = NULL;
    src->end = NULL;
}

int vector_copy(struct vector *src, struct vector *dst) {
    if (src == NULL || dst == NULL) {
        return stat_noerr;
    }
    int ret;
    char *src_block = src->begin;
    if (vector_size(src) > vector_size(dst)) {
        deallocate(dst->begin, vector_size(dst));
        ret = allocate(&dst->begin, vector_size(src));
        if (ret != stat_noerr) {
            return ret;
        }
    }
    char *dst_block = dst->begin;
    for (; src_block != src->cur; ++src_block, ++dst_block) {
        *src_block = *dst_block;
    }
    dst->cur = dst_block;
    dst->end = dst_block;
    return stat_noerr;
}

int vector_pushback(struct vector *vector, char *item) {
    if (item == NULL || vector == NULL) {
        return stat_nothing_done;
    }
    int ret;
    if (vector_is_full(vector)) {
        ret = vector_expand(vector);
        if (ret != stat_noerr) {
            return ret;
        }
    }
    for (size_t i = 0; i < vector->it_size; ++i) {
        vector->cur[i] = item[i];
    }
    vector->cur += vector->it_size;
    return stat_noerr;
}

void vector_popback(struct vector *vector) {
    if (vector_is_empty(vector)) {
        return ;
    }
    vector->cur -= vector->it_size;
}

// iteration
void vector_next(struct vector *vector, char **item) {
    if (item == NULL) {
        return;
    }
    if (vector == NULL) {
        *item = NULL;
        return;
    }
    *item += vector->it_size;
    if (*item == vector->cur) {
        *item = NULL;
    }
}
