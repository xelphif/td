#include "item.h"

#include <stdlib.h>
#include <string.h>

char symbols[2] = { ' ', 'x' };

item_t *item_init(const char *text, bool status)
{
    size_t len  = strlen(text) + 1;
    size_t size = sizeof(char) * len;

    item_t *item = malloc(sizeof(item_t) + size);
    memcpy(item->text, text, size);
    item->status = status;
    item->len    = len;

    return item;
}

item_t *item_set_text(item_t *item, const char *text)
{
    if (!item)
        return NULL;

    size_t len  = strlen(text) + 1;
    size_t size = sizeof(char) * len;

    item = realloc(item, sizeof(item_t) + size);
    memcpy(item->text, text, size);
    item->len = len;

    return item;
}

int item_finish(item_t *item)
{
    if (!item)
        return 1;

    item->status ^= 1;

    return 0;
}
