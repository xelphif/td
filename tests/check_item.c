#include "item.c"
#include "util.h"

struct item *item;

START_TEST(test_item_init)
{
    ck_assert_str_eq(item->text, "text");
    ck_assert_uint_eq(item->len, 5);
    ck_assert_uint_eq(item->status, 0);
}
END_TEST

START_TEST(test_item_set_text)
{
    item_set_text(&item, "new text");

    ck_assert_str_eq(item->text, "new text");
    ck_assert_uint_eq(item->len, 9);

    struct item *null_item = NULL;
    ck_assert_int_eq(item_set_text(&null_item, "text"), 1);
}
END_TEST

START_TEST(test_item_finish)
{
    item_finish(item);

    ck_assert_uint_eq(item->status, 1);

    item_finish(item);

    ck_assert_uint_eq(item->status, 0);
}
END_TEST

START_TEST(test_item_status_s)
{
    ck_assert_uint_eq(item_symbol(item), symbols[0]);

    item->status = 1;

    ck_assert_uint_eq(item_symbol(item), symbols[1]);
}
END_TEST

void setup(void)
{
    item = item_init("text", false);
}

void teardown(void)
{
    free(item);
}

int main()
{
    const TTest *tests[] = {
        test_item_init,
        test_item_set_text,
        test_item_finish,
        test_item_status_s,
        NULL,
    };

    return run_tests("item", tests, setup, teardown);
}
