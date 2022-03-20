#include "cmd.h"
#include "item.h"
#include "serialize.h"

#include <string.h>

static int add_args(int argc, const char **argv, array_t *array)
{
    for (int i = 0; i < argc; i++) {
        size_t len = strlen(argv[i]) + 1;
        a_push(array, init_item(argv[i], len, 0));
    }

    return 0;
}

int cmd_add(int argc, const char **argv, array_t *array)
{
    if (argc < 2)
        return 1;

    add_args(argc - 1, argv + 1, array);

    serialize(FILENAME, array);

    return 0;
}
