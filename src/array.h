#ifndef ARRAY_H
#define ARRAY_H

#define DEFAULT_CAPACITY 1 << 4
#define INDEX_OUT_OF_BOUNDS NULL

typedef struct array {
    void **items;
    unsigned size;
    unsigned capacity;
} array_t;

array_t *init_array();
void a_destroy(array_t *a);
void *a_push(array_t *a, void *value);
void *a_get(array_t *a, const unsigned index);
int a_set(array_t *a, void *value, const unsigned index);
int a_swap(array_t *a, const unsigned x, const unsigned y);
int a_move(array_t *a, const unsigned dest, const unsigned src);
int a_delete(array_t *a, const unsigned index);

#endif
