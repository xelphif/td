#pragma once

#include <stdbool.h>
#include <stddef.h>

struct item {
    bool status;
    size_t len;
    char text[];
};

struct item *item_init(const char *text, bool status);
int item_set_text(struct item **item_ref, const char *text);
int item_finish(struct item *item);
char item_symbol(struct item *item);
