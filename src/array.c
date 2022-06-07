#include "array.h"

#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 1 << 4

struct array *a_init(void)
{
    struct array *a = malloc(sizeof(struct array));
    a->items        = calloc(DEFAULT_CAPACITY, sizeof(void *));
    a->capacity     = DEFAULT_CAPACITY;
    a->size         = 0;

    return a;
}

void a_destroy(struct array *a)
{
    while (a->size)
        a_delete(a, a->size - 1);

    free(a->items);
    free(a);

    return;
}

void *a_push(struct array *a, void *value)
{
    if (a->size >= a->capacity)
        a->items = realloc(a->items, (a->capacity <<= 1) * sizeof(void *));

    a->items[a->size++] = value;

    return value;
}

static int contains(const size_t size, const unsigned int index)
{
    return size >= 0 && index < size;
}

void *a_get(struct array *a, const unsigned int index)
{
    if (!contains(a->size, index))
        return NULL;

    return a->items[index];
}

int a_set(struct array *a, void *value, const unsigned int index)
{
    if (!contains(a->size, index))
        return 1;

    a->items[index] = value;
    return 0;
}

int a_swap(struct array *a, const unsigned int x, const unsigned int y)
{
    if (!contains(a->size, x))
        return 1;
    if (!contains(a->size, y))
        return 1;

    void *temp  = a->items[x];
    a->items[x] = a->items[y];
    a->items[y] = temp;
    return 0;
}

int a_move(struct array *a, const unsigned int dest, const unsigned int src)
{
    if (!contains(a->size, dest))
        return 1;
    if (!contains(a->size, src))
        return 1;

    if (src == dest)
        return 0;

    void *temp = a->items[src];
    if (dest > src)
        memmove(a->items + src, a->items + src + 1,
                sizeof(void *) * (dest - src + 1));
    else
        memmove(a->items + dest + 1, a->items + dest,
                sizeof(void *) * (src - dest));
    a->items[dest] = temp;

    return 0;
}

int a_delete(struct array *a, const unsigned int index)
{
    if (!contains(a->size, index))
        return 1;

    free(a->items[index]);

    if (index + 1 < a->size)
        memmove(a->items + index, a->items + index + 1,
                sizeof(void *) * (a->size - index - 1));

    a->size--;

    if (a->capacity > DEFAULT_CAPACITY && a->size <= a->capacity / 2)
        a->items = realloc(a->items, (a->capacity >>= 1) * sizeof(void *));

    return 0;
}
