#include "item.h"

#include <check.h>
#include <stdlib.h>

item_t *item;

START_TEST(test_item_init)
{
    ck_assert_str_eq(item->text, "text");
    ck_assert_uint_eq(item->len, 5);
    ck_assert_uint_eq(item->status, 0);
}
END_TEST

START_TEST(test_item_set_text)
{
    item = item_set_text(item, "new text");

    ck_assert_str_eq(item->text, "new text");
    ck_assert_uint_eq(item->len, 9);
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
    ck_assert_uint_eq(STATUS_S(item), symbols[0]);

    item->status = 1;

    ck_assert_uint_eq(STATUS_S(item), symbols[1]);
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

Suite *item_suite(void)
{
    Suite *s       = suite_create("item");
    TCase *tc_core = tcase_create("core");

    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, test_item_init);
    tcase_add_test(tc_core, test_item_set_text);
    tcase_add_test(tc_core, test_item_finish);
    tcase_add_test(tc_core, test_item_status_s);
    suite_add_tcase(s, tc_core);

    return s;
}

int main()
{
    int number_failed;

    Suite *s    = item_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return number_failed ? 1 : 0;
}
