#ifndef ARRAY_H
#define ARRAY_H
#define DEFAULT_CAPACITY 1 << 4
#define INDEX_OUT_OF_BOUNDS NULL

typedef struct array
{
  void **items;
  unsigned size;
  unsigned capacity;
} array_t;

array_t *init_array ();
void a_free (array_t *a);
void *a_add (array_t *a, void *value);
void *a_get (array_t *a, const unsigned index);
int a_delete (array_t *a, const unsigned index);
unsigned contains (const unsigned size, const unsigned index);

#endif
