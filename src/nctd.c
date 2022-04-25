#include "cmd.h"
#include "config.h"
#include "screen.h"
#include "serialize.h"

#include <stdio.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
    if (getuid() == 0) {
        fprintf(stderr, "Do not run this program as root\n");
        return 1;
    }

    extract_conf();

    array_t *array = init_array();
    deserialize(array);

    if (argc > 1)
        return cmd_main(argc - 1, argv + 1, array);

    return nc_main(array);
}
