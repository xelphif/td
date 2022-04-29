#pragma once

#include "array.h"

#define HELP_ADD "nctd add [<args>]..."
#define HELP_DELETE "nctd delete [<args>]..."
#define HELP_EDIT "nctd edit <index> <text>"
#define HELP_FINISH "nctd finish [<args>]..."
#define HELP_LS "nctd ls"
#define HELP_MV "nctd mv <src> <dest>"
#define HELP_SORT "nctd sort"
#define HELP_SWAP "nctd swap <index1> <index2>"

int cmd_main(int argc, const char **argv, struct array *array);
/* int is_cmd(const char *cmd); */
int strarg(const char *s);
char *get_cmd_help(const char *cmd);

int cmd_add(int argc, const char **argv, struct array *array);
int cmd_delete(int argc, const char **argv, struct array *array);
int cmd_edit(int argc, const char **argv, struct array *array);
int cmd_finish(int argc, const char **argv, struct array *array);
int cmd_help(int argc, const char **argv, struct array *array);
int cmd_ls(int argc, const char **argv, struct array *array);
int cmd_mv(int argc, const char **argv, struct array *array);
int cmd_sort(int argc, const char **argv, struct array *array);
int cmd_swap(int argc, const char **argv, struct array *array);
