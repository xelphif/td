#include "cmd.h"

#include <string.h>

#include "item.h"
#include "serialize.h"

int cmd_edit(int argc, const char **argv, array_t *array)
{
    if (argc < 3)
        return 1;

    int index;
    if ((index = strarg(argv[1])) == -1)
        return 1;

    item_t *item = a_get(array, index);

    if (!item)
        return 1;

    size_t len = strlen(argv[2]) + 1;
    item = set_text(item, argv[2], len);
    a_set(array, item, index);

    serialize(array);

    return 0;
}
