#include "cmd.h"

#include "item.h"
#include "log.h"

int cmd_edit(int argc, const char **argv, struct array *array)
{
    if (argc <= 2) {
        LOG_ERR(NOT_ENOUGH_ARGS);
        return 1;
    }

    int index;
    if ((index = strarg(argv[1])) == -1) {
        LOG_ERR(INVALID_ARG);
        return 1;
    }

    struct item *item = a_get(array, index);

    if (item_set_text(&item, argv[2])) {
        LOG_ERR(INVALID_ARG);
        return 1;
    }

    a_set(array, item, index);

    return 0;
}
