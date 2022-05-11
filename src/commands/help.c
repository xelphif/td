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

int cmd_help(int argc, const char **argv, array_t *array)
{
    return print_help();
}
