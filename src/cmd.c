#include "cmd.h"
#include "config.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

struct cmd_struct {
    char *cmd;
    int (*fn)(int, const char **, array_t *);
    char *cmd_help;
};

static struct cmd_struct commands[] = {
    {"add",     cmd_add,    HELP_ADD   },
    { "delete", cmd_delete, HELP_DELETE},
    { "edit",   cmd_edit,   HELP_EDIT  },
    { "help",   cmd_help,   NULL       },
    { "finish", cmd_finish, HELP_FINISH},
    { "ls",     cmd_ls,     HELP_LS    },
    { "mv",     cmd_mv,     HELP_MV    },
    { "sort",   cmd_sort,   HELP_SORT  },
    { "swap",   cmd_swap,   HELP_SWAP  }
};

/* functions */

// only returns when input is a valid array index
// if input is invalid, returns -1
int strarg(const char *s)
{
    errno = 0;
    char *endptr;

    int val = strtol(s, &endptr, 10);

    if (s == endptr)
        return -1;

    // check if value is out of range or if
    // the input was invalid
    if (errno != 0)
        return -1;

    return val;
}

static struct cmd_struct *get_cmd(const char *cmd)
{
    for (int i = 0; i < ARRAY_SIZE(commands); i++) {
        struct cmd_struct *p = commands + i;
        if (!strcmp(cmd, p->cmd))
            return p;
    }

    return NULL;
}

char *get_cmd_help(const char *cmd)
{
    struct cmd_struct *cmdp;

    cmdp = get_cmd(cmd);
    if (cmdp)
        return cmdp->cmd_help;

    return NULL;
}

static int run_cmd(struct cmd_struct *cmd, int argc, const char **argv,
                   array_t *array)
{
    int status = cmd->fn(argc, argv, array);
    a_destroy(array);
    free_conf();
    return status;
}

static void handle_cmd(int argc, const char **argv, array_t *array)
{
    struct cmd_struct *cmdp;
    const char *cmd = argv[0];

    if (argc > 1 && !strcmp(argv[1], "--help")) {
        argv[1] = argv[0];
        argv[0] = cmd = "help";
    }

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
    handle_cmd(argc, argv, array);

    return 1;
}
