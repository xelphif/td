#include "cmd.h"

#include <stdio.h>

static char *help_msg = "usage: nctd <command> [<args>]\n\n"
                        "Available subcommands:\n\n"
                        "  add      add an item to the list\n"
                        "  delete   delete an item from the list\n"
                        "  edit     edit an item from the list\n"
                        "  finish   toggle the items status\n"
                        "  help     show this message\n"
                        "  ls       print the list\n"
                        "  mv       move an item in the list\n"
                        "  sort     sort the list\n"
                        "  swap     swap two items in the list\n";

static void print_help()
{
    printf("%s", help_msg);
}

int cmd_help(int argc, const char **argv, array_t *array)
{
    print_help();
    return 0;
}
