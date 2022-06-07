#include "cmd.h"

#include "item.h"

static int fsort(struct array *array)
{
    int last = array->size - 1;
    for (int i = last; i >= 0; i--) {
        struct item *item = a_get(array, i);
        if (item->status) {
            if (i == last) {
                last--;
                continue;
            }

            a_move(array, last, i);
            last--;
        }
    }

    return 0;
}

int cmd_sort(int argc, const char **argv, struct array *array)
{
    fsort(array);

    return 0;
}
