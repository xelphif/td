#include "cmd.h"

#include "log.h"

int cmd_mv(int argc, const char **argv, struct array *array)
{
    if (argc <= 2) {
        LOG_ERR(NOT_ENOUGH_ARGS);
        return 1;
    }

    int src  = strarg(argv[1]);
    int dest = strarg(argv[2]);

    if (src == -1 || dest == -1) {
        LOG_ERR(INVALID_ARG);
        return 1;
    }

    int status = a_move(array, dest, src);

    return status;
}
