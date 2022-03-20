#include "cmd.h"
#include "item.h"
#include "serialize.h"

#include <stdio.h>

static int
fsort (array_t *array)
{
  int last = array->size - 1;
  for (int i = last; i >= 0; i--)
    {
      item_t *item = a_get (array, i);
      if (item->status)
        {
          if (i == last)
            {
              last--;
              continue;
            }

          a_move (array, last, i);
          last--;
        }
    }

  return 0;
}

int
cmd_sort (int argc, const char **argv, array_t *array)
{
  fsort (array);

  serialize (FILENAME, array);
  return 0;
}
