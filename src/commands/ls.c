#include "cmd.h"
#include "item.h"

#include <stdio.h>

static void print_array(array_t *array)
{
    if (!array->size)
        puts("No list found.");

    for (int i = 0; i < array->size; i++) {
        item_t *item = a_get(array, i);
        printf("%d. %s %s\n", i, STATUS_S(item), item->text);
    }
}

int cmd_ls(int argc, const char **argv, array_t *array)
{
    if (argc > 1)
        return 1;

    print_array(array);

    return 0;
}
