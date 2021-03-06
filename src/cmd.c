#include "cmd.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

struct cmd_struct {
    char *cmd;
    int (*fn)(int, const char **, struct array *);
};

static struct cmd_struct commands[] = {
    {"add",     cmd_add   },
    { "rm",     cmd_rm    },
    { "edit",   cmd_edit  },
    { "help",   cmd_help  },
    { "finish", cmd_finish},
    { "ls",     cmd_ls    },
    { "mv",     cmd_mv    },
    { "sort",   cmd_sort  },
    { "swap",   cmd_swap  }
};

/* functions */

// only returns when input is a valid array index
// if input is invalid, returns -1
int strarg(const char *s)
{
    errno = 0;
    char *endptr;
    int val = strtol(s, &endptr, 10);

    if (s == endptr || errno != 0)
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

int handle_cmd(int argc, const char **argv, struct array *array)
{
    struct cmd_struct *cmdp;
    const char *cmd = argv[0];

    if (!cmd)
        cmd = "ls";

    if (argc > 1 && !strcmp(argv[1], "--help")) {
        argv[1] = argv[0];
        argv[0] = cmd = "help";
    }

    cmdp = get_cmd(cmd);
    if (cmdp)
        return cmdp->fn(argc, argv, array);

    LOG_ERR("command not found");
    return 1;
}
