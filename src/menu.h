#ifndef MENU_H
#define MENU_H

#include "array.h"

#include <ncurses.h>

typedef struct menu {
    int x;
    int y;
    char mark;
    int cur_item;
    array_t *array;
    WINDOW *win;
    int lines;
    int pos;
} menu_t;

extern int rows, cols;

menu_t *init_menu(array_t *array);

void draw_menu(menu_t *menu);

void move_mark_o(menu_t *menu, int offset);
void swap_mitem_o(menu_t *menu, int offset);
void toggle_mitem(menu_t *menu);
void add_prompt(menu_t *menu);
void edit_prompt(menu_t *menu);
/* void edit_prompt_i(menu_t *menu); */
void delete_mitem(menu_t *menu);
void sort_marray(menu_t *menu);
void handle_resize(menu_t *menu);
void goto_first(menu_t *menu);
void goto_last(menu_t *menu);

int fsort(array_t *array);

#endif
