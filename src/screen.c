#include "screen.h"
#include "item.h"
#include "serialize.h"

#include <ncurses.h>
#include <string.h>

#define CURS_S(x, y) (x) == (y) ? ">" : " "
#define PADDING 2

enum p_states { LIST, HELP };
int p_state;

// TODO:
//  window drawing functions
//  input functions
//      add function shows realtime preview
//      of item in the list (with resizing)
//  resize functions
//  string cropping ?
//  minimum size ?
//  cleanup function
static int rows, cols, curs_index;

static int init_nc(void)
{
    initscr();

    cbreak();
    noecho();
    curs_set(0);

    getmaxyx(stdscr, rows, cols);

    return 0;
}

static int close_nc(void)
{
    endwin();

    return 0;
}

static void pitem(int y, int x, array_t *array, int index)
{
    item_t *item = a_get(array, index);
    mvprintw(y, x, "%s %s %s", CURS_S(curs_index, index), STATUS_S(item),
             item->text);
}

static void plist(array_t *array)
{
    for (int i = 0; i < array->size; i++) {
        pitem(PADDING + i, PADDING, array, i);
    }
}

static void draw_help(void)
{
    mvprintw(PADDING, PADDING, "%s", "NCTD HELP");
    mvprintw(PADDING + 2, PADDING, "%c  %s", '?', "show help screen");
    mvprintw(PADDING + 4, PADDING, "%c  %s", 'j', "move selection down");
    mvprintw(PADDING + 5, PADDING, "%c  %s", 'k', "move selection up");
    mvprintw(PADDING + 6, PADDING, "%c  %s", 'a', "add list item");
    mvprintw(PADDING + 7, PADDING, "%c  %s", 'd', "delete list item");
    mvprintw(PADDING + 8, PADDING, "%c  %s", 'e', "edit list item");
    mvprintw(PADDING + 9, PADDING, "%c  %s", 's', "sort list by status");
    mvprintw(PADDING + 10, PADDING, "%c  %s", 'w', "save list to file");
}

static void draw_screen(array_t *array)
{
    switch (p_state) {
        case LIST:
            plist(array);
            break;
        case HELP:
            draw_help();
            break;
    }
}

static void add_list(array_t *array)
{
    erase();
    plist(array);
    mvprintw(PADDING + array->size, PADDING, "  %s ", "[ ]");

    curs_set(2);
    echo();
    char buf[120];
    getnstr(buf, 120);
    noecho();
    curs_set(0);

    size_t len = strlen(buf);
    if (!len++)
        return;

    a_push(array, init_item(buf, len, 0));
    curs_index = array->size - 1;
}

static void delete_list(array_t *array)
{
    a_delete(array, curs_index);
    if (curs_index >= array->size)
        curs_index = array->size - 1;
}

static void edit_list(array_t *array)
{
    item_t *item = a_get(array, curs_index);

    if (!item)
        return;

    mvprintw(PADDING + curs_index, PADDING, "> %s ", STATUS_S(item));
    clrtoeol();

    curs_set(2);
    echo();
    char buf[80];
    getnstr(buf, 80);
    noecho();
    curs_set(0);

    size_t len = strlen(buf);
    if (!len++)
        return;

    item = set_text(item, buf, len);
    a_set(array, item, curs_index);
}

static void handle_input(array_t *array)
{
    int c;
    while ((c = getch()) != 'q') {
        switch (c) {
            case '?':
                p_state ^= HELP;
                break;
            case 'J':
                if (curs_index < array->size - 1)
                    a_swap(array, curs_index, curs_index + 1);
            case 'j':
                curs_index++;
                if (curs_index >= array->size)
                    curs_index = array->size - 1;
                break;
            case 'K':
                if (curs_index > 0)
                    a_swap(array, curs_index, curs_index - 1);
            case 'k':
                curs_index--;
                if (curs_index <= -1)
                    curs_index = 0;
                break;
            case 'a':
                add_list(array);
                break;
            case 'd':
                delete_list(array);
                break;
            case 'e':
                edit_list(array);
                break;
            case 10:
            case 'x':
                finish_item(a_get(array, curs_index));
                break;
            case 's':
                fsort(array);
                break;
            case 'w':
                serialize(FILENAME, array);
                break;
            case KEY_RESIZE:
                getmaxyx(stdscr, rows, cols);
                break;
        }
        erase();
        draw_screen(array);
    }
}

int nc_main(array_t *array)
{
    init_nc();

    plist(array);

    handle_input(array);

    close_nc();

    return 0;
}
