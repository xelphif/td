#include "cmd.h"
#include "strarg.h"
#include "serialize.h"

#include <stdio.h>

int cmd_delete(int argc, const char **argv, array_t *array)
{
    int index;
    if ((index = strarg(argv[1])) == -1)
        return 1;

    a_delete(array, index);

    serialize(FILENAME, array);

    return 0;
}
