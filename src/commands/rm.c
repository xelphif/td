#include "cmd.h"

#include <stdlib.h>
#include <string.h>

#include "item.h"
#include "log.h"
#include "serialize.h"

static int delete_finished(struct array *array)
{
    int status = 0;
    for (int i = 0; i < array->size; i++) {
        struct item *item = a_get(array, i);
        if (item->status)
            status = a_delete(array, i--);
    }

    return status;
}

static int delete_arg(const char *arg, struct array *array)
{
    int index;
    if ((index = strarg(arg)) == -1) {
        LOG_ERR("no valid argument found, aborting")
        return 1;
    }

    int status = a_delete(array, index);

    return status;
}

int cmd_rm(int argc, const char **argv, struct array *array)
{
    if (argc <= 1) {
        LOG_ERR(NOT_ENOUGH_ARGS);
        return 1;
    }

    if (!strcmp(argv[1], "finished"))
        return delete_finished(array);

    return delete_arg(argv[1], array);
}
