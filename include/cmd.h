#ifndef _TD_CMD_H
#define _TD_CMD_H

#include "array.h"

int handle_cmd(int argc, const char **argv, struct array *array);
int strarg(const char *s);

int cmd_add(int argc, const char **argv, struct array *array);
int cmd_rm(int argc, const char **argv, struct array *array);
int cmd_edit(int argc, const char **argv, struct array *array);
int cmd_finish(int argc, const char **argv, struct array *array);
int cmd_help(int argc, const char **argv, struct array *array);
int cmd_ls(int argc, const char **argv, struct array *array);
int cmd_mv(int argc, const char **argv, struct array *array);
int cmd_sort(int argc, const char **argv, struct array *array);
int cmd_swap(int argc, const char **argv, struct array *array);

#endif
