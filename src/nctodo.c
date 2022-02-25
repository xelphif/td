#include <ncurses.h>
#include <string.h>

#include "task.h"
#include "screen.h"

int main(int argc, char *argv[]) {
    task_t **tasks = load_list(FILENAME);

    initscr();
    curs_set(0);
    noecho();
    cbreak();

    getmaxyx(stdscr, mrow, mcol);
    wrow = LWIN_MROW, wcol = LWIN_MCOL;
    WINDOW *listwin = newwin(wrow, wcol,
            LWIN_INITY, LWIN_INITX);

    scrollok(listwin, TRUE);
    box(stdscr, 0, 0);
    refresh();
    wprintw_list(listwin, tasks);

    int c;
    while ((c = getch()) != 'q') {
        switch (c) {
            case 'j' :
                wrap_hl(&highlight,  1);
                break;
            case 'k' :
                wrap_hl(&highlight, -1);
                break;
            case 'd' :
                tasks = delete_task(tasks, highlight);
                wrap_hl(&highlight,  0);
                break;
            case 'a' :
                tasks = wadd_prompt(listwin, tasks);
                break;
            case 10 :
                if (!used)
                    continue;
                finish_task(tasks[highlight]);
                break;
            case KEY_RESIZE :
                resize_screen(listwin);
                break;
        }

        wprintw_list(listwin, tasks);
    }

    delwin(listwin);
    endwin();
    free_list(tasks);

    return 0;
}
