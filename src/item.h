#ifndef ITEM_H
#define ITEM_H

typedef struct item {
    unsigned finished;
    char text[];
} item_t;

item_t *init_item(const char *text, unsigned len, unsigned finished);

item_t *set_text(item_t *item, const char *text, unsigned len);

void finish_item(item_t *item);

#endif
