#include "cmd.h"

#include <stdio.h>

#include "item.h"
#include "log.h"

static int print_array(array_t *array)
{
    if (!array->size) {
        LOG_WARN("No list found.");
        return 1;
    }

    for (int i = 0; i < array->size; i++) {
        item_t *item = a_get(array, i);
        printf("%2d. [%c] %s\n", i, STATUS_S(item), item->text);
    }

    return 0;
}

int cmd_ls(int argc, const char **argv, array_t *array)
{
    return print_array(array);
}
