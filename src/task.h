#ifndef NODE_H
#define NODE_H

#define FILENAME    "TODO"
#define DONE_S_LEN  4
#define INIT_SIZE   16

static char   done_s[DONE_S_LEN]   = "[x]";
static char n_done_s[DONE_S_LEN]   = "[ ]";

typedef struct TASK {
    int finished;
    int deleted;
    char text[];
} task_t;

typedef struct INFO {
    size_t size;
    size_t used;
    size_t longest;
} info_t;

task_t *init_task (char *text, size_t len, int finished);
info_t *init_info ();
task_t **list_add    (task_t **tasks, task_t *task, info_t *info);
void  delete_task (task_t *task, info_t *info);
void  finish_task (task_t *task);
char *finish_s    (int finished);

task_t **load_list  (char *filename, info_t *info);
void     dump_list  (char *filename, task_t **tasks, info_t *info);
void     free_list  (task_t **tasks, info_t *info);
void     print_list (task_t **tasks, info_t *info);

#endif
