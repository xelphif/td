#ifndef ITEM_H
#define ITEM_H

typedef struct item {
    unsigned status;
    unsigned len;
    int x;
    int y;
    char text[];
} item_t;

#define STATUS_S(x) conf->symbols[(x)->status]

item_t *init_item(const char *text, unsigned len, unsigned finished);
item_t *set_text(item_t *item, const char *text, unsigned len);
int finish_item(item_t *item);

#endif
