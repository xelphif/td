#include "cmd.h"
#include "item.h"
#include "serialize.h"

#include <stdio.h>

static int finish_args(int argc, const char **argv, array_t *array)
{
    for (int i = 0; i < argc; i++) {
        int index;
        if ((index = strarg(argv[i])) == -1)
            continue;

        finish_item(a_get(array, index));
    }

    return 0;
}

int cmd_finish(int argc, const char **argv, array_t *array)
{
    if (argc < 2)
        return 1;

    finish_args(argc - 1, argv + 1, array);

    serialize(array);

    return 0;
}
