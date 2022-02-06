#ifndef NODE_H
#define NODE_H

#define FILENAME    "TODO"
#define DONE_S_LEN  4
#define INIT_SIZE   10

static char   done_s[DONE_S_LEN]   = "[x]";
static char n_done_s[DONE_S_LEN]   = "[ ]";

typedef struct TASK {
    int finished;
    int deleted;
    char *text;
} task_t;

task_t *init_task (char *text, size_t len, int finished);
task_t **list_add (task_t **tasks, task_t *task, size_t *used, size_t *size);
void  delete_task (task_t *task);
void  finish_task (task_t *task);
char *finish_s    (int finished);

task_t **load_list  (char *filename, size_t *n_tasks, size_t *size);
void     dump_list  (char *filename, task_t **tasks, size_t used);
void     free_list  (task_t **tasks, size_t used);
void     print_list (task_t **tasks, size_t used);

#endif
