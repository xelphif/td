#ifndef ITEM_H
#define ITEM_H

typedef struct item {
    unsigned status;
    char text[];
} item_t;

#define STATUS_S(x) (x)->status ? "[x]" : "[ ]"

item_t *init_item(const char *text, unsigned len, unsigned finished);
item_t *set_text(item_t *item, const char *text, unsigned len);
int finish_item(item_t *item);

#endif
