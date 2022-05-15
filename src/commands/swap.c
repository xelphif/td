#include "cmd.h"

#include "log.h"
#include "serialize.h"

int cmd_swap(int argc, const char **argv, array_t *array)
{
    if (argc < 3)
        return 1;

    int x = strarg(argv[1]);
    int y = strarg(argv[2]);

    if (x == -1 || y == -1) {
        LOG_ERR(INVALID_ARG);
        return 1;
    }

    int status = a_swap(array, x, y);

    serialize(array);

    return status;
}
