#include "screen.h"
#include "config.h"
#include "item.h"
#include "menu.h"
#include "serialize.h"

#include <ncurses.h>
#include <string.h>

// TODO:
//  window drawing functions
//  input functions
//      add function shows realtime preview
//      of item in the list (with resizing)
//  resize functions
//  string cropping ?
//  minimum size ?
//  cleanup function

int rows, cols;

static int init_nc(void)
{
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

    return 0;
}

static void print_debug(menu_t *menu)
{
    mvwprintw(stdscr, 0, 20, "ROWS:%d COLS:%d POS:%d LAST_VIS:%d CUR_ITEM:%d",
              rows, cols, menu->pos, menu->pos + rows - 1, menu->cur_item);
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
                goto_first(menu);
                break;
            case 'G':
                goto_last(menu);
                break;
            case 'w':
                serialize(FILENAME, menu->array);
                break;
            case KEY_RESIZE:
                handle_resize(menu);
                break;
                /* case 'E': */
                /*     edit_prompt_i(menu); */
                /*     break; */
                /* case KEY_RESIZE: */
                /*     getmaxyx(stdscr, rows, cols); */
                /*     break; */
        }
        print_debug(menu);
    }
}

int nc_main(array_t *array)
{
    init_nc();

    menu_t *menu = init_menu(array);

    refresh();
    draw_menu(menu);

    handle_input(menu);

    close_nc(menu);

    return 0;
}
