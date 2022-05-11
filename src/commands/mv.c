#include "cmd.h"

#include "serialize.h"

int cmd_mv(int argc, const char **argv, struct array *array)
{
    if (argc < 3)
        return 1;

    int src = strarg(argv[1]);
    int dest = strarg(argv[2]);

    if (src == -1 || dest == -1)
        return 1;

    int status = a_move(array, dest, src);

    serialize(array);

    return status;
}
