#include "cmd.h"

#include <stdio.h>

static const char *help_msg = "usage: nctd <command> [<args>]\n\n"
                              "Available subcommands:\n\n"
                              "  add      add item to the list\n"
                              "  rm       remove item from the list\n"
                              "  edit     edit item from the list\n"
                              "  finish   toggle item status\n"
                              "  help     show this message\n"
                              "  ls       print the list\n"
                              "  mv       move item in the list\n"
                              "  sort     sort the list\n"
                              "  swap     swap two items in the list\n";

int cmd_help(int argc, const char **argv, struct array *array)
{
    puts(help_msg);
    return 0;
}
