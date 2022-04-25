#include "item.h"
#include "config.h"

#include <stdlib.h>
#include <string.h>

item_t *init_item(const char *text, unsigned len, unsigned status)
{
    unsigned size = sizeof(char) * len;
    item_t *item = malloc(sizeof(item_t) + size);
    memcpy(item->text, text, size);
    item->status = status;
    item->len = len;

    return item;
}

item_t *set_text(item_t *item, const char *text, unsigned len)
{
    if (!item)
        return NULL;

    unsigned size = sizeof(char) * len;
    item = realloc(item, sizeof(item_t) + size);
    memcpy(item->text, text, size);
    item->len = len;

    return item;
}

int finish_item(item_t *item)
{
    if (!item)
        return 1;

    item->status ^= 1;

    return 0;
}
