#include "cmd.h"

#include "log.h"

int cmd_swap(int argc, const char **argv, struct array *array)
{
    if (argc <= 2)
        return 1;

    int x = strarg(argv[1]);
    int y = strarg(argv[2]);

    if (x == -1 || y == -1) {
        LOG_ERR(INVALID_ARG);
        return 1;
    }

    int status = a_swap(array, x, y);

    return status;
}
