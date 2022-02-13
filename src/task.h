#ifndef TASK_H
#define TASK_H

#define FILENAME    "TODO"
#define DONE_S_LEN  4
#define ARRAY_INIT_SIZE   16

extern char   done_s[DONE_S_LEN];
extern char n_done_s[DONE_S_LEN];

extern int size, used, longest;

typedef struct TASK {
    int finished;
    char text[];
} task_t;

task_t  *init_task   (char *text, size_t len, int finished);
task_t **list_add    (task_t **tasks, task_t *task);
task_t **delete_task (task_t **tasks, int remove_index);
void     finish_task (task_t *task);
char    *finish_s    (int finished);

task_t **load_list  (char *filename);
void     dump_list  (char *filename, task_t **tasks);
void     free_list  (task_t **tasks);

#endif
