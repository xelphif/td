#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "screen.h"

#define BUF_SIZE 120

int mrow, mcol, wrow, wcol;
int highlight = 0;

task_t **wadd_prompt(WINDOW *win, task_t **tasks) {
    mvwprintw(win, wrow - 2, 2, "Add item: ");
    wrefresh(win);
    curs_set(2);
    echo();

    char buf[BUF_SIZE];
    int len;

    if (wgetnstr(win, buf, BUF_SIZE) != ERR) {
        len = strlen(buf);
        tasks = list_add(tasks, init_task(buf, len + 1, 0));
    }

    noecho();
    curs_set(0);

    return tasks;
}

void resize_screen(WINDOW *win) {
    getmaxyx(stdscr, mrow, mcol);
    wrow = LWIN_MROW, wcol = LWIN_MCOL;
    wresize(win, wrow, wcol);

    werase(stdscr);
    box(stdscr, 0, 0);
    refresh();
}

void wprintw_list(WINDOW *win, task_t **tasks) {
    werase(win);

    if (used) {
        for (int i = 0; i < used; i++) {
            if (i == highlight) wattron(win, A_REVERSE);
            mvwprintw(win, (wrow - used) / 2 + i,
                    (wcol - longest) / 2,
                    "%s %s\n",
                    finish_s(tasks[i]->finished),
                    tasks[i]->text);
            if (i == highlight) wattroff(win, A_REVERSE);
        }
    }

    wrefresh(win);
}

void wrap_hl(int *hl, int inc) {
    *hl += inc;

    if (*hl == used)
        *hl = used - 1;
    if (*hl == -1)
        *hl = 0;
}
