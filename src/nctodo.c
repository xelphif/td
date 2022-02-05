#include <ncurses.h>

#include "node.h"

int main() {
    int ch;

    node_t *head = load_list(FILENAME);

    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    print_list(printw, head);

    getch();
    endwin();
}
