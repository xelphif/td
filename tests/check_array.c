#include "array.h"

#include <check.h>
#include <stdlib.h>

array_t *a;

char *string_from(const char *str)
{
    char *s = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(s, str);

    return s;
}

START_TEST(test_array_init)
{
    ck_assert_ptr_nonnull(a);
    ck_assert_ptr_nonnull(a->items);
    ck_assert_uint_eq(a->size, 0);
    ck_assert_uint_eq(a->capacity, 16);
}
END_TEST

START_TEST(test_array_push)
{
    a_push(a, string_from("string 1"));
    a_push(a, string_from("string 2"));
    a_push(a, string_from("string 3"));
    a_push(a, string_from("string 4"));
    a_push(a, string_from("string 5"));
    a_push(a, string_from("string 6"));
    a_push(a, string_from("string 7"));
    a_push(a, string_from("string 8"));
    a_push(a, string_from("string 9"));
    a_push(a, string_from("string 10"));
    a_push(a, string_from("string 11"));
    a_push(a, string_from("string 12"));
    a_push(a, string_from("string 13"));
    a_push(a, string_from("string 14"));
    a_push(a, string_from("string 15"));
    a_push(a, string_from("string 16"));
    a_push(a, string_from("string 17"));

    ck_assert_str_eq(a_get(a, 0), "string 1");
    ck_assert_str_eq(a_get(a, 1), "string 2");
    ck_assert_str_eq(a_get(a, 2), "string 3");
    ck_assert_str_eq(a_get(a, 16), "string 17");
    ck_assert_uint_eq(a->size, 17);
    ck_assert_uint_eq(a->capacity, 32);
}
END_TEST

START_TEST(test_array_get)
{
    a->size     = 1;
    a->items[0] = string_from("string");

    ck_assert_str_eq(a_get(a, 0), "string");
    ck_assert_ptr_null(a_get(a, 1000));
}
END_TEST

START_TEST(test_array_swap)
{
    a->size     = 2;
    a->items[0] = string_from("x");
    a->items[1] = string_from("y");

    a_swap(a, 0, 1);

    ck_assert_str_eq(a->items[0], "y");
    ck_assert_str_eq(a->items[1], "x");

    ck_assert_int_eq(a_swap(a, 0, 1000), 1);
}
END_TEST

START_TEST(test_array_move)
{
    a->size     = 3;
    a->items[0] = string_from("string 1");
    a->items[1] = string_from("string 2");
    a->items[2] = string_from("string 3");

    a_move(a, 0, 2);

    ck_assert_str_eq(a->items[0], "string 3");
    ck_assert_str_eq(a->items[1], "string 1");
    ck_assert_str_eq(a->items[2], "string 2");

    a_move(a, 2, 0);

    ck_assert_str_eq(a->items[0], "string 1");
    ck_assert_str_eq(a->items[1], "string 2");
    ck_assert_str_eq(a->items[2], "string 3");
}

START_TEST(test_array_delete)
{
    a->size     = 3;
    a->items[0] = string_from("string 1");
    a->items[1] = string_from("string 2");
    a->items[2] = string_from("string 3");

    a_delete(a, 1);

    ck_assert_str_eq(a->items[0], "string 1");
    ck_assert_str_eq(a->items[1], "string 3");

    ck_assert_int_eq(a_delete(a, 1000), 1);
}
END_TEST

static void setup()
{
    a = a_init();
}

static void teardown()
{
    a_destroy(a);
}

Suite *array_suite(void)
{
    Suite *s       = suite_create("array");
    TCase *tc_core = tcase_create("core");

    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, test_array_init);
    tcase_add_test(tc_core, test_array_push);
    tcase_add_test(tc_core, test_array_get);
    tcase_add_test(tc_core, test_array_swap);
    tcase_add_test(tc_core, test_array_move);
    tcase_add_test(tc_core, test_array_delete);
    suite_add_tcase(s, tc_core);

    return s;
}

int main()
{
    int number_failed;

    Suite *s    = array_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return number_failed ? 1 : 0;
}
