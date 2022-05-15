#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct item {
    bool status;
    size_t len;
    char text[];
} item_t;

extern char symbols[2];

#define STATUS_S(x) symbols[(x)->status]

item_t *item_init(const char *text, bool status);
item_t *item_set_text(item_t *item, const char *text);
int item_finish(item_t *item);
