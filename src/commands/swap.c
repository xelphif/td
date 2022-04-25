#include "cmd.h"
#include "serialize.h"

int cmd_swap(int argc, const char **argv, array_t *array)
{
    if (argc < 3)
        return 1;

    int x = strarg(argv[1]);
    int y = strarg(argv[2]);

    if (x < 0 || y < 0)
        return 1;

    int status = a_swap(array, x, y);

    serialize(array);

    return status;
}
