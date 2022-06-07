#include "array.c"
#include "util.h"

struct array *a;

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
    a_push(a, strdup("string 1"));
    a_push(a, strdup("string 2"));
    a_push(a, strdup("string 3"));
    a_push(a, strdup("string 4"));
    a_push(a, strdup("string 5"));
    a_push(a, strdup("string 6"));
    a_push(a, strdup("string 7"));
    a_push(a, strdup("string 8"));
    a_push(a, strdup("string 9"));
    a_push(a, strdup("string 10"));
    a_push(a, strdup("string 11"));
    a_push(a, strdup("string 12"));
    a_push(a, strdup("string 13"));
    a_push(a, strdup("string 14"));
    a_push(a, strdup("string 15"));
    a_push(a, strdup("string 16"));
    a_push(a, strdup("string 17"));

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
    a->items[0] = strdup("string");

    ck_assert_str_eq(a_get(a, 0), "string");
    ck_assert_ptr_null(a_get(a, 1000));
}
END_TEST

START_TEST(test_array_swap)
{
    a->size     = 2;
    a->items[0] = strdup("x");
    a->items[1] = strdup("y");

    a_swap(a, 0, 1);

    ck_assert_str_eq(a->items[0], "y");
    ck_assert_str_eq(a->items[1], "x");

    ck_assert_int_eq(a_swap(a, 0, 1000), 1);
}
END_TEST

START_TEST(test_array_move)
{
    a->size     = 3;
    a->items[0] = strdup("string 1");
    a->items[1] = strdup("string 2");
    a->items[2] = strdup("string 3");

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
    a->items[0] = strdup("string 1");
    a->items[1] = strdup("string 2");
    a->items[2] = strdup("string 3");

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

int main()
{
    const TTest *tests[] = {
        test_array_init, test_array_push,   test_array_get, test_array_swap,
        test_array_move, test_array_delete, NULL,
    };

    return run_tests("array", tests, setup, teardown);
}
