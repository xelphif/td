#include "array.h"
#include "item.h"
#include "serialize.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "TODO.json"

void
print_usage ()
{
  printf ("Usage: [options] [arguments]\n");
}

void print_array (array_t *array);

int
main (int argc, char *argv[])
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

  int option_index = 0;
  while (
      (opt = getopt_long (argc, argv, "a:d:c:", long_options, &option_index))
      != -1)
    {
      switch (opt)
        {
        case 'a':
          len = strlen (optarg) + 1;
          a_add (array, init_item (optarg, len, 0));
          mod = 1;
          break;
        case 'd':
          a_delete (array, atoi (optarg));
          mod = 1;
          break;
        case 'c':
          finish_item (a_get (array, atoi (optarg)));
          mod = 1;
          break;
        default:
          print_usage ();
          return 1;
          break;
        }
    }
  print_array (array);

  if (mod)
    {
      if (serialize (FILENAME, array))
        remove (FILENAME);
    }

  a_destroy (array);

  return 0;
}

void
print_array (array_t *array)
{
  if (!array)
    return;

  item_t *item;
  for (int i = 0; i < array->size; i++)
    {
      item = a_get (array, i);
      printf ("%s %s\n", item->finished ? "[x]" : "[ ]", item->text);
    }

  return;
}
