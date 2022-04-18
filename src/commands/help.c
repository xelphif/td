#include "cmd.h"

#include <stdio.h>

static const char *help_msg = "usage: nctd <command> [<args>]\n\n"
                        "Available subcommands:\n\n"
                        "  add      add item to the list\n"
                        "  delete   delete item from the list\n"
                        "  edit     edit item from the list\n"
                        "  finish   toggle item status\n"
                        "  help     show this message\n"
                        "  ls       print the list\n"
                        "  mv       move item in the list\n"
                        "  sort     sort the list\n"
                        "  swap     swap two items in the list\n";

static int print_help()
{
    puts(help_msg);
    return 0;
}

static int print_cmd_help(const char *cmd) {
    char *help_str;

    help_str = get_cmd_help(cmd);

    if (help_str) {
        puts(help_str);
        return 0;
    }

    puts("command not found");
    print_help();
    return 1;
}

int cmd_help(int argc, const char **argv, array_t *array)
{
    if (argc > 1)
       return print_cmd_help(argv[1]);

    return print_help();
}
