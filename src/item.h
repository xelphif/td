#ifndef ITEM_H
#define ITEM_H

typedef struct item {
    unsigned int status;
    char text[];
} item_t;

#define STATUS_S(x) (x)->status ? "[x]" : "[ ]"

item_t *init_item(const char *text, unsigned int len, unsigned int finished);
item_t *set_text(item_t *item, const char *text, unsigned int len);
int finish_item(item_t *item);

#endif
