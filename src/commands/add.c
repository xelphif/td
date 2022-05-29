#include "cmd.h"

#include "item.h"
#include "log.h"

#include <stdio.h>

static int add_args(int argc, const char **argv, array_t *array)
{
    for (int i = 0; i < argc; i++) {
        a_push(array, item_init(argv[i], false));
    }

    return 0;
}

int cmd_add(int argc, const char **argv, array_t *array)
{
    if (argc < 2) {
        LOG_ERR(NOT_ENOUGH_ARGS);
        return 1;
    }

    add_args(argc - 1, argv + 1, array);

    return 0;
}
