#ifndef LIST_H
#define LIST_H

extern int visible, firstvis;
extern int aindex, highlight;
extern int col, row, mcol, mrow;

void move_select(int inc, task_t **tasks, info_t *info);
void delete_select(task_t **tasks, info_t *info);
task_t **add_select(WINDOW *win, task_t **tasks, info_t *info);
void wrap(int *num, int lower, int higher);
void printscr(WINDOW *win, int saved, task_t **tasks, info_t *info);
void print_border();

#endif
