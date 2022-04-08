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

#define LAST_ITEM(x) (x)->array->size - 1
#define VIS_ITEMS(x) (x)->pos + rows - 1
#define MAX_POS(x) (x)->array->size - rows

extern int rows, cols;

menu_t *init_menu(array_t *array);
void free_menu(menu_t *menu);

void draw_menu(menu_t *menu);

void move_mark_o(menu_t *menu, int offset);
void move_mark_i(menu_t *menu, int index);
void swap_mitem_o(menu_t *menu, int offset);
void toggle_mitem(menu_t *menu);
void add_prompt(menu_t *menu);
void edit_prompt(menu_t *menu);
/* void edit_prompt_i(menu_t *menu); */
void delete_mitem(menu_t *menu);
void sort_marray(menu_t *menu);
void handle_resize(menu_t *menu);

int fsort(array_t *array);

#endif
