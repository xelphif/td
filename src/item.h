#pragma once

#include <stdbool.h>

typedef struct item {
    bool status;
    unsigned len;
    char text[];
} item_t;

extern char symbols[2];

#define STATUS_S(x) symbols[(x)->status]

item_t *init_item(const char *text, unsigned len, bool status);
item_t *set_text(item_t *item, const char *text, unsigned len);
int finish_item(item_t *item);
