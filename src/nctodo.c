#include <ncurses.h>
#include <string.h>

#include "task.h"
#include "nctodo.h"

int main() {
    int ch;
    int saved = 0;

    info_t *info = init_info();
    task_t **tasks = load_list(FILENAME, info);
    visible = info->used;

    initscr();
    curs_set(0);
    raw();
    keypad(stdscr, TRUE);
    noecho();

    printscr(saved, tasks, info);
    while ((ch = getch()) != 'q') {
        saved = 0;
        switch (ch) {
            case 'j' :
                move_select(1, tasks, info);
                break;
            case 'k' :
                move_select(-1, tasks, info);
                break;
            case 'd' :
                delete_select(tasks, info);
                break;
            case 'a' :
                tasks = add_select(tasks, info);
                break;
            case 'w' :
                dump_list(FILENAME, tasks, info);
                saved = 1;
                break;
            case 10 :
                finish_task(tasks[aindex]);
                break;
            case KEY_RESIZE :
                printscr(saved, tasks, info);
                break;
        }
        printscr(saved, tasks, info);
    }
    endwin();
    free_list(tasks, info);
}

void move_select(int inc, task_t **tasks, info_t *info) {
    if (visible == 0)
        return;

    highlight += inc;
    aindex += inc;

    wrap(&highlight, -1, visible);
    wrap(&aindex, -1, info->used);
    while (tasks[aindex]->deleted) {
        aindex += inc;
        wrap(&aindex, -1, info->used);
    }
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
}

task_t **add_select(task_t **tasks, info_t *info) {
    char buf[80];
    size_t len;

    mvprintw(row - 2, 2 , "Add task: ");
    noraw();
    curs_set(2);
    echo();
    getnstr(buf, 80);
    noecho();
    curs_set(0);
    raw();

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

void print_stats(int hl, int i, info_t *info) {
    mvprintw(2, 2, "HL: %d | i = %d | VISIBLE: %d | FIRSTVIS: %d | USED: %d ",
            hl, i, visible, firstvis, info->used);
}

void wprint_list(task_t **tasks, info_t *info) {
    int line = 0;
    for (int i = 0; i < info->used; i++) {
        if (tasks[i]->deleted)
            continue;

        if (line == highlight) { wattron(stdscr, A_REVERSE); }
        mvprintw((row - visible) / 2 + line, (col - info->longest) / 2,
                "%s %s\n", finish_s(tasks[i]->finished), tasks[i]->text);
        if (line == highlight) { wattroff(stdscr, A_REVERSE); }
        line++;
    }

    box(stdscr, 0, 0);
}

void printscr(int saved, task_t **tasks, info_t *info) {
    erase();
    getmaxyx(stdscr, row, col);

    wprint_list(tasks, info);

    if (DEBUG)
        print_stats(highlight, aindex, info);
    if (saved)
        mvprintw(2, col - 21, "List saved to file.");
}
