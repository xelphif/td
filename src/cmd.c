#include "cmd.h"

#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

struct cmd_struct {
    char *cmd;
    int (*fn)(int, const char **, array_t *);
};

static struct cmd_struct commands[] = {
    {"add",     cmd_add   },
    { "delete", cmd_delete},
    { "edit",   cmd_edit  },
    { "help",   cmd_help  },
    { "finish", cmd_finish},
    { "ls",     cmd_ls    },
    { "mv",     cmd_mv    },
    { "sort",   cmd_sort  },
    { "swap",   cmd_swap  }
};

#define HELP_CMD commands + 3

/* functions */

static struct cmd_struct *get_cmd(const char *cmd)
{
    for (int i = 0; i < ARRAY_SIZE(commands); i++) {
        struct cmd_struct *p = commands + i;
        if (!strcmp(cmd, p->cmd))
            return p;
    }

    return HELP_CMD;
}

static int run_cmd(struct cmd_struct *cmd, int argc, const char **argv,
                   array_t *array)
{
    int status = cmd->fn(argc, argv, array);
    a_destroy(array);
    return status;
}

static void handle_cmd(int argc, const char **argv, array_t *array)
{
    struct cmd_struct *cmdp;
    const char *cmd = argv[0];

    cmdp = get_cmd(cmd);
    if (cmdp)
        exit(run_cmd(cmdp, argc, argv, array));
}

/* int is_cmd(const char *cmd) */
/* { */
/*     return !!get_cmd(cmd); */
/* } */

int cmd_main(int argc, const char **argv, array_t *array)
{
    const char *cmd;

    cmd = argv[0];
    if (!cmd)
        cmd = "help";

    argv[0] = cmd;

    handle_cmd(argc, argv, array);

    return 1;
}
