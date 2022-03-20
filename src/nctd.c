#include "array.h"
#include "cmd.h"
#include "serialize.h"

#include <stdio.h>

int main(int argc, const char *argv[])
{
    array_t *array = init_array();
    deserialize(FILENAME, array);

    if (argc > 1)
        return cmd_main(argc - 1, argv + 1, array);

    puts("NCURSES MODE");
    return 0;
}
