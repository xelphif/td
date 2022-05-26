#include "cmd.h"

#include "item.h"
#include "log.h"
#include "serialize.h"

int cmd_edit(int argc, const char **argv, array_t *array)
{
    if (argc < 3) {
        LOG_ERR(NOT_ENOUGH_ARGS);
        return 1;
    }

    int index;
    if ((index = strarg(argv[1])) == -1) {
        LOG_ERR(INVALID_ARG);
        return 1;
    }

    item_t *item = a_get(array, index);

    if (item_set_text(&item, argv[2])) {
        LOG_ERR(INVALID_ARG);
        return 1;
    }

    a_set(array, item, index);

    serialize(array);

    return 0;
}
