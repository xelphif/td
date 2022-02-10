#include <ncurses.h>
#include <string.h>

#include "task.h"

// TODO: make info global (extern?) since it appears
// in virtually every function call; declutter
// TODO: rework info? perhaps too many variables to track
// TODO: redo entire thing... this is disgusting
//
//      -- Step 1: create ONE function that handles
//         keeping track of both higlight and index
//
//      -- Step 2: highlight and index are visible
//         to the entire program, like info and tasks
//         will be. However this info and tasks
//         may stay local due to the possibility
//         of multiple lists and and infos attached
//         to them
//
//         What is more likely is that info will
//         come bundled with a task array somehow
//
//      -- Cleaning up the switch statement should
//         be priority, then maybe cleaning the
//         functions. Looking for a different approach
//         to the index incrementer as opposed to
//         recursion would also be optimal.
//         There remains the possibility of infinite
//         recursion if the entire list is deleted
//         while the program is running

int visible;
void inchl(int *highlight, int inc);
void inci(int *i, int inc, task_t **tasks, info_t *info);
void print_stats(int hl, int i, info_t *info);
void wprint_list(task_t **tasks, info_t *info, int highlight);

int main() {
    int ch, len, highlight = 0, aindex = 0;
    char buf[80];

    info_t *info = init_info();
    task_t **tasks = load_list(FILENAME, info);
    visible = info->used;

    initscr();
    curs_set(0);
    raw();
    keypad(stdscr, TRUE);
    noecho();

    wprint_list(tasks, info, highlight);
    // print_stats(highlight, aindex, info);

    while ((ch = getch()) != 'q') {
        switch (ch) {
            case 'j' :
                inchl(&highlight, 1);
                inci(&aindex, 1, tasks, info);
                break;
            case 'k' :
                inchl(&highlight, -1);
                inci(&aindex, -1, tasks, info);
                break;
            case 'd' :
                delete_task(tasks[aindex], info);
                visible--;
                if (highlight == visible) {
                    inchl(&highlight, -1);
                    inci(&aindex, -1, tasks, info);
                }
                else
                    inci(&aindex, 1, tasks, info);
                break;
            case 'a' :
                mvprintw(2, 2, "Add item: ");
                echo();
                getstr(buf);
                noecho();
                len = strlen(buf);
                list_add(tasks, init_task(buf, len + 1, 0), info);
                visible++;
                break;
            case 'w' :
                dump_list(FILENAME, tasks, info);
                break;
            case 10 :
                finish_task(tasks[aindex]);
                break;
            case KEY_RESIZE :
                break;
        }
        wprint_list(tasks, info, highlight);
        // print_stats(highlight, aindex, info);
    }
    endwin();

    free_list(tasks, info);
}

void inchl(int *highlight, int inc) {
    *highlight += inc;
    if (*highlight == -1)
        *highlight = visible - 1;
    if (*highlight == visible)
        *highlight = 0;
}

void inci(int *i, int inc, task_t **tasks, info_t *info) {
    *i += inc;
    if (*i == -1)
        *i = info->used - 1;
    if (*i == info->used)
        *i = 0;
    if (tasks[*i]->deleted) {
        inci(i, inc, tasks, info);
    }
}

void print_stats(int hl, int i, info_t *info) {
    mvprintw(2, 2, "HL: %d | i = %d | VISIBLE: %d | USED: %d ", hl, i, visible, info->used);
}

void wprint_list(task_t **tasks, info_t *info, int highlight) {
    erase();

    int row, col, line = 0;
    getmaxyx(stdscr, row, col);
    for (int i = 0; i < info->used; i++) {
        if (tasks[i]->deleted)
            continue;

        if (line == highlight) {
            wattron(stdscr, A_REVERSE);
            mvprintw((row - visible) / 2 + line, (col - info->longest) / 2,
                "%s %s\n", finish_s(tasks[i]->finished), tasks[i]->text);
            wattroff(stdscr, A_REVERSE);
        } else {
            mvprintw((row - visible) / 2 + line, (col - info->longest) / 2,
                "%s %s\n", finish_s(tasks[i]->finished), tasks[i]->text);
        }
        line++;
    }

    box(stdscr, 0, 0);
}
