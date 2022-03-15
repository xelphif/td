#include "cmd.h"
#include "item.h"
#include "serialize.h"
#include "strarg.h"

#include <stdio.h>

int cmd_finish(int argc, const char **argv, array_t *array)
{
    int index;
    if ((index = strarg(argv[1])) == -1)
        return 1;

    int status = finish_item(a_get(array, index));

    if (!status)
        serialize(FILENAME, array);

    return status;
}
