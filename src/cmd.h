#pragma once

#include "array.h"

int handle_cmd(int argc, const char **argv, struct array *array);
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
