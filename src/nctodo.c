#include "array.h"
#include "item.h"
#include "serialize.h"

#include <stdio.h>

#define FILENAME "TODO.json"

void print_array(array_t *array);

int main() {
  int mod = 0;

  array_t *array = init_array();
  deserialize(FILENAME, array);

  print_array(array);

  if (array->size && mod)
    serialize(FILENAME, array);
}

void print_array(array_t *array) {
  item_t *item;
  for (int i = 0; i < array->size; i++) {
    item = a_get(array, i);
    printf("%d %s\n", item->finished, item->text);
  }
}
