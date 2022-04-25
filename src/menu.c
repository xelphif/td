#include "menu.h"
#include "array.h"
#include "config.h"
#include "item.h"

#include <stdlib.h>
#include <string.h>

#define MARK(x, y) (y) == (x)->cur_item ? conf->menu_marker : " "
#define ITEM_PREFIX(x) strlen(conf->menu_marker) + strlen(STATUS_S(x)) + 4

static void set_itemyx(menu_t *menu)
{
    for (int i = 0; i < menu->array->size; i++) {
        item_t *item = a_get(menu->array, i);

        item->y = menu->y + i;
        item->x = menu->x;
    }
}

menu_t *init_menu(array_t *array)
{
    menu_t *menu = malloc(sizeof(menu_t));

    menu->x = 0;
    menu->y = 0;

    menu->cur_item = 0;

    menu->array = array;

    set_itemyx(menu);

    menu->lines = menu->array->capacity;
    menu->win = newpad(menu->lines, cols);
    keypad(menu->win, TRUE);
    menu->pos = 0;

    return menu;
}

void free_menu(menu_t *menu)
{
    free(menu);
}

static void refresh_menu(menu_t *menu)
{
    prefresh(menu->win, menu->pos, 0, conf->pad_y, conf->pad_x,
             rows - 1 - (conf->pad_y * 2), cols - 1 - (conf->pad_x * 2));
}

static void resize_menu(menu_t *menu)
{
    wresize(menu->win, menu->lines + (menu->y * 2) + 1, cols);
}

static int is_visible(menu_t *menu, int x)
{
    if (x > VIS_ITEMS(menu))
        return 1;
    if (x < menu->pos)
        return -1;

    return 0;
}

static void winchk(menu_t *menu)
{
    if (menu->lines != menu->array->capacity) {
        werase(menu->win);
        refresh_menu(menu);
        menu->lines = menu->array->capacity;
        resize_menu(menu);
    }
}

void draw_menu(menu_t *menu)
{
    for (int i = 0; i < menu->array->size; i++) {
        item_t *item = a_get(menu->array, i);

        wmove(menu->win, item->y, item->x);

        waddstr(menu->win, MARK(menu, i));
        waddch(menu->win, ' ');

        waddch(menu->win, '[');
        waddstr(menu->win, STATUS_S(item));
        waddch(menu->win, ']');
        waddch(menu->win, ' ');

        waddnstr(menu->win, item->text, item->len);
    }

    refresh_menu(menu);
}

void update_menu(menu_t *menu)
{
    werase(menu->win);
    draw_menu(menu);
}

void move_mark_o(menu_t *menu, int offset)
{
    menu->cur_item += offset;

    if (menu->cur_item <= -1)
        menu->cur_item = 0;
    if (menu->array->size && menu->cur_item >= menu->array->size)
        menu->cur_item = LAST_ITEM(menu);

    menu->pos += is_visible(menu, menu->cur_item);

    update_menu(menu);
}

void move_mark_i(menu_t *menu, int index)
{
    menu->cur_item = index;

    if (is_visible(menu, index))
        menu->pos = index > MAX_POS(menu) ? MAX_POS(menu) : index;

    update_menu(menu);
}

void swap_mitem_o(menu_t *menu, int offset)
{
    a_swap(menu->array, menu->cur_item, menu->cur_item + offset);
    set_itemyx(menu);
}

void toggle_mitem(menu_t *menu)
{
    finish_item(a_get(menu->array, menu->cur_item));
    update_menu(menu);
}

void delete_mitem(menu_t *menu)
{
    a_delete(menu->array, menu->cur_item);
    winchk(menu);
    set_itemyx(menu);
    move_mark_o(menu, -1);
}

static int pgetnstr(menu_t *menu, char *buf, int n)
{
    int c, y, x, i = 0, len = 0;
    while ((c = wgetch(menu->win)) != '\n') {
        switch (c) {
            case KEY_LEFT:
                if (i <= 0)
                    continue;
                i--;
                getyx(menu->win, y, x);
                wmove(menu->win, y, --x);
                refresh_menu(menu);
                continue;
            case KEY_RIGHT:
                if (i >= len)
                    continue;
                i++;
                getyx(menu->win, y, x);
                wmove(menu->win, y, ++x);
                refresh_menu(menu);
                continue;
            case KEY_BACKSPACE:
            case 127:
            case 8:
                if (len == 0)
                    return 0;
                if (i <= 0)
                    continue;
                getyx(menu->win, y, x);
                wmove(menu->win, y, --x);
                i--;
            case KEY_DC:
                if (i == len)
                    continue;
                memmove(buf + i, buf + i + 1, sizeof(char) * (len-- - i));
                wdelch(menu->win);
                refresh_menu(menu);
                continue;
            case 27:
                return 0;
            case KEY_RESIZE:
                return 0;
        }

        if (len == n - 1)
            continue;

        if (i < len - 1)
            memmove(buf + i + 1, buf + i, sizeof(char) * len - i);
        ;
        buf[i++] = c;
        len++;

        getyx(menu->win, y, x);
        winsch(menu->win, c);
        wmove(menu->win, y, ++x);
        refresh_menu(menu);
    }

    buf[len] = '\0';

    return len;
}

void add_prompt(menu_t *menu)
{
    int last_pos = menu->pos;
    if (is_visible(menu, menu->array->size))
        menu->pos = MAX_POS(menu) + 1;
    wmove(menu->win, menu->array->size, menu->x);

    waddch(menu->win, '+');
    waddch(menu->win, ' ');

    waddnstr(menu->win, "[ ]", 3);
    waddch(menu->win, ' ');

    refresh_menu(menu);

    char buf[120];

    curs_set(2);

    int len;
    if ((len = pgetnstr(menu, buf, 120))) {
        a_push(menu->array, init_item(buf, len + 1, 0));
        menu->cur_item = LAST_ITEM(menu);
    } else
        menu->pos = last_pos;

    curs_set(0);

    winchk(menu);
    set_itemyx(menu);
    update_menu(menu);
}

void edit_prompt(menu_t *menu)
{
    item_t *item = a_get(menu->array, menu->cur_item);
    wmove(menu->win, item->y, item->x + ITEM_PREFIX(item));

    for (int i = 0; i < item->len; i++)
        waddch(menu->win, ' ');

    wmove(menu->win, item->y, item->x + ITEM_PREFIX(item));

    refresh_menu(menu);

    char buf[120];

    curs_set(2);

    int len;
    if ((len = pgetnstr(menu, buf, 120)))
        set_text(item, buf, len + 1);

    curs_set(0);

    update_menu(menu);
}

/* void edit_prompt_i(menu_t *menu) */
/* { */
/*     item_t *item = a_get(menu->array, menu->cur_item); */
/*     wmove(menu->win, menu->y + menu->cur_item, menu->x + ITEM_PREFIX); */
/*     refresh_menu(menu->win); */

/*     char buf[120]; */
/*     memcpy(buf, item->text, sizeof(char) * item->len); */

/*     curs_set(2); */

/*     int len; */
/*     if ((len = pgetnstr(menu->win, buf, 120))) */
/*         set_text(item, buf, len); */

/*     curs_set(0); */

/*     update_menu(menu); */
/* } */

void sort_marray(menu_t *menu)
{
    fsort(menu->array);
    set_itemyx(menu);
    update_menu(menu);
}

void handle_resize(menu_t *menu)
{
    refresh();
    getmaxyx(stdscr, rows, cols);
    resize_menu(menu);
    if (is_visible(menu, menu->cur_item))
        menu->pos = menu->cur_item;
    if (VIS_ITEMS(menu) > LAST_ITEM(menu))
        menu->pos = MAX_POS(menu);
    update_menu(menu);
}
