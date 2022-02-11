#define DEBUG 0

int visible, firstvis = 0;
int aindex = 0, highlight = 0;
int col, row;
void move_select(int inc, task_t **tasks, info_t *info);
void delete_select(task_t **tasks, info_t *info);
task_t **add_select(task_t **tasks, info_t *info);
void wrap(int *num, int lower, int higher);
void printscr(int saved, task_t **tasks, info_t *info);
void print_stats(int hl, int i, info_t *info);
void wprint_list(task_t **tasks, info_t *info);
