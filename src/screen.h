#ifndef SCREEN_H
#define SCREEN_H

extern int mcol, mrow;
extern int wcol, wrow;
extern int help, save;
extern int highlight;

#define LWIN_INITY 2
#define LWIN_INITX 2
#define LWIN_MROW mrow - (LWIN_INITX * 2)
#define LWIN_MCOL mcol - (LWIN_INITY * 2)

task_t **wadd_prompt(WINDOW *win, task_t **tasks);
void resize_screen(WINDOW *win);

void print_screen();
void wprintw_list(WINDOW *win, task_t **tasks);
void wrap_hl(int *hl, int inc);

#endif
