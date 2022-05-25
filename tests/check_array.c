#include "array.h"

#include <check.h>

START_TEST(test_array_init) {
    array_t *a = a_init();

    ck_assert(a);
    ck_assert(a->items);
    ck_assert_uint_eq(a->size, 0);
    ck_assert_uint_eq(a->capacity, 16);
}
END_TEST

Suite *array_suite(void) {
    Suite *s = suite_create("array");
    TCase *tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_array_init);
    suite_add_tcase(s, tc_core);

    return s;
}

int main() {
    int number_failed;

    Suite *s = array_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return number_failed ? 1 : 0;
}
