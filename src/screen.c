#include "screen.h"
#include "config.h"
#include "item.h"
#include "menu.h"
#include "serialize.h"

#include <locale.h>
#include <string.h>

int rows, cols;

static int init_nc(void)
{
    setlocale(LC_ALL, "");

    initscr();

    cbreak();
    noecho();
    curs_set(0);

    getmaxyx(stdscr, rows, cols);

    return 0;
}

static int close_nc(menu_t *menu)
{
    delwin(menu->win);
    endwin();

    a_destroy(menu->array);
    free_menu(menu);

    return 0;
}

static void handle_input(menu_t *menu)
{
    int c;
    // int pos = 0;
    while ((c = getch()) != 'q') {
        switch (c) {
            case 'J':
                swap_mitem_o(menu, 1);
            case 'j':
                move_mark_o(menu, 1);
                break;
            case 'K':
                swap_mitem_o(menu, -1);
            case 'k':
                move_mark_o(menu, -1);
                break;
            case 10:
                toggle_mitem(menu);
                break;
            case 'a':
                add_prompt(menu);
                break;
            case 'd':
                delete_mitem(menu);
                break;
            case 'e':
                edit_prompt(menu);
                break;
            case 's':
                sort_marray(menu);
                break;
            case 'g':
                move_mark_i(menu, 0);
                break;
            case 'G':
                move_mark_i(menu, LAST_ITEM(menu));
                break;
            case 'w':
                serialize(menu->array);
                break;
            case KEY_RESIZE:
                handle_resize(menu);
                break;
        }
    }
}

int nc_main(array_t *array)
{
    setlocale(LC_ALL, "");

    init_nc();

    menu_t *menu = init_menu(array);

    refresh();
    draw_menu(menu);

    handle_input(menu);

    close_nc(menu);

    return 0;
}
