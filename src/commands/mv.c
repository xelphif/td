#include "cmd.h"
#include "serialize.h"
#include "strarg.h"

int cmd_mv(int argc, const char **argv, struct array *array)
{
    if (argc < 3)
        return 1;

    int src = strarg(argv[1]);
    int dest = strarg(argv[2]);

    if (src < 0 || dest < 0)
        return 1;

    int status = a_move(array, dest, src);

    serialize(FILENAME, array);

    return status;
}
