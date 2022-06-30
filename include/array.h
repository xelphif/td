#ifndef _TD_ARRAY_H
#define _TD_ARRAY_H

#include <stddef.h>

struct array {
    void **items;
    size_t size;
    size_t capacity;
};

struct array *a_init(void);
void a_destroy(struct array *a);
void *a_push(struct array *a, void *value);
void *a_get(struct array *a, const unsigned int index);
int a_set(struct array *a, void *value, const unsigned int index);
int a_swap(struct array *a, const unsigned int x, const unsigned int y);
int a_move(struct array *a, const unsigned int dest, const unsigned int src);
int a_delete(struct array *a, const unsigned int index);

#endif
