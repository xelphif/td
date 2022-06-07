#include "item.h"

#include <stdlib.h>
#include <string.h>

char symbols[2] = { ' ', 'x' };

struct item *item_init(const char *text, bool status)
{
    size_t len  = strlen(text) + 1;
    size_t size = sizeof(char) * len;

    struct item *item = malloc(sizeof(struct item) + size);
    memcpy(item->text, text, size);
    item->status = status;
    item->len    = len;

    return item;
}

int item_set_text(struct item **item_ref, const char *text)
{
    if (!*item_ref)
        return 1;

    size_t len  = strlen(text) + 1;
    size_t size = sizeof(char) * len;

    *item_ref = realloc(*item_ref, sizeof(struct item) + size);
    memcpy((*item_ref)->text, text, size);
    (*item_ref)->len = len;

    return 0;
}

int item_finish(struct item *item)
{
    if (!item)
        return 1;

    item->status ^= 1;

    return 0;
}

char item_symbol(struct item *item)
{
    static char symbols[] = { ' ', 'x' };

    return symbols[item->status];
}
