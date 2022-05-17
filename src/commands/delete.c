#include "cmd.h"

#include <stdlib.h>
#include <string.h>

#include "item.h"
#include "log.h"
#include "serialize.h"

static int delete_finished(array_t *array)
{
    int status = 0;
    for (int i = 0; i < array->size; i++) {
        item_t *item = a_get(array, i);
        if (item->status)
            status = a_delete(array, i--);
    }

    serialize(array);

    return status;
}

static int cmp(const void *a, const void *b)
{
    int x = *(int *)a;
    int y = *(int *)b;
    if (x > y)
        return -1;
    if (x < y)
        return 1;
    else
        return 0;
}

static int delete_args(int argc, const char **argv, array_t *array)
{
    int valid_args[argc];
    memset(valid_args, 0, sizeof(valid_args));
    int valid = 0;

    // collect all valid indices
    for (int i = 0; i < argc; i++) {
        int index;
        if ((index = strarg(argv[i])) == -1)
            continue;

        if (index >= 0 && index < array->size)
            valid_args[valid++] = index;
    }

    if (!valid) {
        LOG_ERR("no valid arguments found, aborting")
        return 1;
    }

    // sort all valid indexes in descending order
    qsort(valid_args, valid, sizeof(int), cmp);

    int last_deleted = -1;
    for (int i = 0; i < valid; i++) {
        if (valid_args[i] == last_deleted)
            continue;

        a_delete(array, valid_args[i]);
        last_deleted = valid_args[i];
    }

    serialize(array);

    return 0;
}

int cmd_delete(int argc, const char **argv, array_t *array)
{
    if (argc < 2) {
        LOG_ERR(NOT_ENOUGH_ARGS);
        return 1;
    }

    if (!strcmp(argv[1], "all"))
        return file_delete();

    if (!strcmp(argv[1], "finished"))
        return delete_finished(array);

    return delete_args(argc - 1, argv + 1, array);
}
