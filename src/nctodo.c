// #include "node.h"

// int main() {
//     int ch;
//
//     node_t *head = load_list(FILENAME);
//
//     initscr();
//     raw();
//     keypad(stdscr, TRUE);
//     noecho();
//
//     print_list(printw, head);
//
//     getch();
//     endwin();
// }

#include <stdio.h>
#include <stdlib.h>
#include <menu.h>
#include <form.h>

#include "node.h"

int main()
{
    ITEM **items;
    int c;
    MENU *menu;
    int n_nodes, i;
    ITEM *cur_item;

    node_t *head = load_list(FILENAME, &n_nodes);

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    items = calloc(n_nodes + 1, sizeof(ITEM *));
    node_t *curr = head;
    for (i = 0; curr != NULL; i++) {
        items[i] = new_item(curr->task, checks(curr->check));
        curr = curr->next;
    }
    items[n_nodes] = NULL;

    menu = new_menu(items);
    post_menu(menu);
    refresh();

    while((c = getch()) != 'q') {
        switch (c) {
            case 'j':
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case 'k':
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case 'a':
                break;
        }
    }

    dump_list(head, FILENAME);
    free_list(head);
    for (int i = 0; items[i] != NULL; i++)
        free_item(items[i]);
    free_menu(menu);
    endwin();
}
