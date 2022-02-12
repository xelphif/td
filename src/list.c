#include <ncurses.h>
#include <string.h>

#include "task.h"
#include "list.h"

#define DEBUG 1

void find_next_visible();
void print_stats(WINDOW *win, int hl, int i, info_t *info);
void wprint_list(WINDOW *win, task_t **tasks, info_t *info);

int visible, firstvis = 0;
int highlight = 0, aindex = 0;
int col, row;
int mrow, mcol;

struct command_desc {
    char *key;
    char *desc;
};

static struct command_desc commands[] = {
    { "q",      "quit"                },
    { "j",      "move selection down" },
    { "k",      "move selection up"   },
    { "d",      "delete selection"    },
    { "a",      "add item"            },
    { "w",      "save list to file"   },
    { "ENTER",  "mark as done"        }
};

void move_select(int inc, task_t **tasks, info_t *info) {
    if (visible == 0)
        return;

    highlight += inc;
    aindex += inc;

    wrap(&highlight, -1, visible);
    wrap(&aindex, -1, info->used);
    find_next_visible(inc, tasks, info);
}

void delete_select(task_t **tasks, info_t *info) {
    if (visible == 0)
        return;

    delete_task(tasks[aindex], info);
    visible--;

    if (highlight == visible) {
        move_select(-1, tasks, info);
        return;
    }

    if (aindex == firstvis)
        firstvis++;
    aindex++;
    find_next_visible(1, tasks, info);
}

task_t **add_select(WINDOW *win, task_t **tasks, info_t *info) {
    char buf[80];
    size_t len;

    mvwprintw(win, row - 2, 2 , "Add task: ");

    curs_set(2);
    getnstr(buf, 80);
    curs_set(0);

    len = strlen(buf);
    tasks = list_add(tasks, init_task(buf, len, 0), info);

    if (len > info->longest)
        info->longest = len;

    visible++;

    return tasks;
}

void wrap(int *num, int lower, int higher) {
    if (*num == lower)
        *num = higher - 1;
    if (*num == higher)
        *num = lower + 1;
}

void find_next_visible(int inc, task_t **tasks, info_t *info) {
    while (tasks[aindex]->deleted) {
        aindex += inc;
        wrap(&aindex, -1, info->used);
    }
}

void print_stats(WINDOW *win, int hl, int i, info_t *info) {
    mvwprintw(win, 2, 2, "HL: %d | i = %d | VISIBLE: %d | FIRSTVIS: %d | USED: %ld ",
            hl, i, visible, firstvis, info->used);
}

void wprint_list(WINDOW *win, task_t **tasks, info_t *info) {
    int line = 0;
    for (int i = 0; i < info->used; i++) {
        if (tasks[i]->deleted)
            continue;

        if (line == highlight) { wattron(win, A_REVERSE); }
        mvwprintw(win, (row - visible) / 2 + line, (col - info->longest) / 2,
                "%s %s\n", finish_s(tasks[i]->finished), tasks[i]->text);
        if (line == highlight) { wattroff(win, A_REVERSE); }
        line++;
    }
}

void printscr(WINDOW *win, int saved, task_t **tasks, info_t *info) {
    werase(win);
    getmaxyx(win, row, col);

    wprint_list(win, tasks, info);

    if (DEBUG)
        print_stats(win, highlight, aindex, info);
    if (saved)
        mvwprintw(win, 2, col - 21, "List saved to file.");

    box(win, 0, 0);

    wrefresh(win);
}

void print_border() {
    werase(stdscr);
    getmaxyx(stdscr, mrow, mcol);
    box(stdscr, 0, 0);
}
