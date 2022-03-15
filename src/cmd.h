#ifndef CMD_H
#define CMD_H

#include "array.h"

int cmd_main(int argc, const char **argv, struct array *array);
int is_cmd(const char *cmd);

int cmd_add(int argc, const char **argv, struct array *array);
int cmd_delete(int argc, const char **argv, struct array *array);
int cmd_edit(int argc, const char **argv, struct array *array);
int cmd_finish(int argc, const char **argv, struct array *array);
int cmd_help(int argc, const char **argv, struct array *array);
int cmd_ls(int argc, const char **argv, struct array *array);
int cmd_mv(int argc, const char **argv, struct array *array);
int cmd_sort(int argc, const char **argv, struct array *array);
int cmd_swap(int argc, const char **argv, struct array *array);

#endif
