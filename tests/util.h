#include <check.h>

Suite *gen_suite(char *name, const TTest *tests[], void (*setup)(void),
                 void (*teardown)(void))
{
    Suite *s  = suite_create(name);
    TCase *tc = tcase_create("core");

    if (setup && teardown)
        tcase_add_checked_fixture(tc, setup, teardown);

    for (int i = 0; tests[i]; i++)
        tcase_add_test(tc, tests[i]);

    suite_add_tcase(s, tc);

    return s;
}

int run_tests(char *name, const TTest *tests[], void (*setup)(void),
              void (*teardown)(void))
{
    int number_failed;

    Suite *s    = gen_suite(name, tests, setup, teardown);
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return number_failed ? 1 : 0;
}
