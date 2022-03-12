#include "array.h"
#include <stdlib.h>
#include <string.h>

array_t *
init_array ()
{
  array_t *a = malloc (sizeof (array_t));
  a->items = calloc (DEFAULT_CAPACITY, sizeof (void *));
  a->capacity = DEFAULT_CAPACITY;
  a->size = 0;

  return a;
}

void *
a_add (array_t *a, void *value)
{
  if (a->size >= a->capacity)
    a->items = realloc (a->items, (a->capacity <<= 1) * sizeof (void *));

  a->items[a->size++] = value;

  return value;
}

void *
a_get (array_t *a, const unsigned index)
{
  if (!contains (a->size, index))
    return INDEX_OUT_OF_BOUNDS;

  return a->items[index];
}

int
a_delete (array_t *a, const unsigned index)
{
  if (!contains (a->size, index))
    return 1;

  free (a->items[index]);

  if (index + 1 < a->size)
    memmove (a->items + index, a->items + index + 1,
             sizeof (void *) * (a->size - index - 1));

  a->size--;

  return 0;
}

unsigned
contains (const unsigned size, const unsigned index)
{
  if (size >= 0 && index < size)
    return 1;

  return 0;
}
