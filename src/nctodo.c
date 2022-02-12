#include <ncurses.h>

#include "task.h"
#include "list.h"

#define WINSTARTX 1
#define WINSTARTY 1

int main() {
    int ch;
    int saved = 0;

    info_t *info = init_info();
    task_t **tasks = load_list(FILENAME, info);
    visible = info->used;

    // customize ncurses behavior
    initscr();
    curs_set(0);
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    print_border();
    refresh();

    // set up list window
    WINDOW *listwin = newwin(mrow - (WINSTARTY * 2), mcol - (WINSTARTX * 2), WINSTARTY, WINSTARTX);
    printscr(listwin, saved, tasks, info);

    // set up help window


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
                tasks = add_select(listwin, tasks, info);
                break;
            case 'w' :
                dump_list(FILENAME, tasks, info);
                saved = 1;
                break;
            case 10 :
                finish_task(tasks[aindex]);
                break;
            case KEY_RESIZE :
                printscr(listwin, saved, tasks, info);
                break;
        }
        printscr(listwin, saved, tasks, info);
    }
    delwin(listwin);
    endwin();
    free_list(tasks, info);
}
