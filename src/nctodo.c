#include "array.h"
#include "item.h"
#include "serialize.h"

#include <getopt.h>
#include <stdio.h>
#include <string.h>

#define FILENAME "TODO.json"

void print_array (array_t *array);

int
main ()
{
  array_t *array = init_array ();
  deserialize (FILENAME, array);

  int opt = 0, mod = 0;
  size_t len;

  static struct option long_options[]
      = { { "add", required_argument, 0, 'a' },
          { "delete", required_argument, 0, 'd' },
          { "check", required_argument, 0, 'c' },
          { 0, 0, 0, 0 } };

  print_array (array);

  if (array->size && mod)
    serialize (FILENAME, array);
}

void
print_array (array_t *array)
{
  item_t *item;
  for (int i = 0; i < array->size; i++)
    {
      item = a_get (array, i);
      printf ("%d %s\n", item->finished, item->text);
    }
}
