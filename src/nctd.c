#include "array.h"
#include "cmd.h"
#include "serialize.h"

#include <stdio.h>

int main(int argc, const char *argv[])
{
    array_t *array = init_array();
    deserialize(FILENAME, array);

    // size_t len;

    // TODO: replace getopt with subcommand system
    //    List of planned subcommands
    //        add:    1 (optional numerical) argument and one string
    //        clear:  no arguments
    //        delete: 1 argument (numerical)
    //        edit:   1 argument (numerical) and one string
    //        finish: 1 argument (numerical)
    //        ls:     no arguments
    //        sort:   1 argument (string) mode
    //                OR 1 argument and only one fixed sorting mode
    //        swap:   2 arguments (numerical)
    //
    //        if argv[1] is not one of the subcommands, display
    //        usage and exit failure

    // a_destroy(array);

    if (argc > 1)
        return cmd_main(argc - 1, argv + 1, array);

    puts("NCURSES MODE");
    return 0;
}
