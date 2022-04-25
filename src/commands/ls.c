#include "cmd.h"
#include "config.h"
#include "item.h"

#include <stdio.h>

static int print_array(array_t *array)
{
    if (!array->size) {
        fprintf(stderr, "No list found.\n");
        return 1;
    }

    for (int i = 0; i < array->size; i++) {
        item_t *item = a_get(array, i);
        printf("%2d. [%s] %s\n", i, STATUS_S(item), item->text);
    }

    return 0;
}

int cmd_ls(int argc, const char **argv, array_t *array)
{
    if (argc > 1)
        return 1;

    return print_array(array);
}
