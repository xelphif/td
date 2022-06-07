#include "cmd.h"

#include <stdio.h>

#include "item.h"
#include "log.h"

static int print_array(struct array *array)
{
    if (!array->size) {
        LOG_WARN("no list found");
        return 1;
    }

    for (int i = 0; i < array->size; i++) {
        struct item *item = a_get(array, i);
        printf("%2d. [%c] %s\n", i, item_symbol(item), item->text);
    }

    return 0;
}

int cmd_ls(int argc, const char **argv, struct array *array)
{
    return print_array(array);
}
