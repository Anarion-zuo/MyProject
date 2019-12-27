//
// Created by anarion on 2019/11/2.
//

#include "list.h"
#include "../erronos.h"
#include "allocator.h"

struct node {
    char *data;
    struct node *prev, *next;
};

struct list {
    struct node head;
    size_t it_size;
};

int list_init(struct list *list, size_t it_size) {
    if (list == NULL) {
        return stat_nothing_done;
    }
    list->head.prev = &list->head;
    list->head.next = &list->head;
    list->it_size = it_size;
    return stat_noerr;
}

int list_pushback(struct list *list, char *item) {
    struct node *tail = list->head.prev, *node;
    int ret;
    ret = allocate((char **) &node, sizeof(struct node));
    if (ret != stat_noerr) {
        return ret;
    }
    node->prev = tail;
    tail->next = node;
    node->next = &list->head;
    list->head.prev = node;
    ret = allocate(&node, list->it_size);
    if (ret != stat_noerr) {
        return ret;
    }
    for (size_t i = 0; i < list->it_size; ++i) {
        node->data[i] = item[i];
    }
    return stat_noerr;
}

int list_pushfront(struct list *list, char *item) {
    struct node *head = list->head.prev, *node;
    int ret;
    ret = allocate((char **) &node, sizeof(struct node));
    if (ret != stat_noerr) {
        return ret;
    }
    node->next = head;
    head->prev = node;
    list->head.next = node;
    node->prev = list->head.next;
    ret = allocate(&node, list->it_size);
    if (ret != stat_noerr) {
        return ret;
    }
    for (size_t i = 0; i < list->it_size; ++i) {
        node->data[i] = item[i];
    }
    return stat_noerr;
}