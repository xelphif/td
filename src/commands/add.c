#include "cmd.h"
#include "item.h"
#include "serialize.h"

#include <string.h>

int cmd_add(int argc, const char **argv, array_t *array)
{
    if (argc < 2)
        return 1;

    size_t len = strlen(argv[1]) + 1;
    a_push(array, init_item(argv[1], len, 0));

    serialize(FILENAME, array);

    return 0;
}
