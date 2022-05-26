#include "array.h"

#include <stdio.h>
#include <unistd.h>

#include "cmd.h"
#include "log.h"
#include "serialize.h"

int main(int argc, const char *argv[])
{
    if (getuid() == 0) {
        LOG_ERR("do not run as root");
        return 1;
    }

    array_t *array = a_init();
    deserialize(array);

    int status = handle_cmd(argc - 1, argv + 1, array);
    a_destroy(array);
    return status;
}
