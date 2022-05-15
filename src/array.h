#pragma once

#include <stddef.h>

typedef struct array {
    void **items;
    size_t size;
    size_t capacity;
} array_t;

array_t *a_init(void);
void a_destroy(array_t *a);
void *a_push(array_t *a, void *value);
void *a_get(array_t *a, const unsigned int index);
int a_set(array_t *a, void *value, const unsigned int index);
int a_swap(array_t *a, const unsigned int x, const unsigned int y);
int a_move(array_t *a, const unsigned int dest, const unsigned int src);
int a_delete(array_t *a, const unsigned int index);
