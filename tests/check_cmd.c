#include "cmd.c"
#include "util.h"

/* stubs */
int cmd_finish(int argc, const char **argv, struct array *array)
{
    return -1;
}

int cmd_help(int argc, const char **argv, struct array *array)
{
    return -1;
}

int cmd_mv(int argc, const char **argv, struct array *array)
{
    return -1;
}

int cmd_sort(int argc, const char **argv, struct array *array)
{
    return -1;
}

enum cmd_return { ADD, ERR, RM, EDIT, LS, SWAP };

int cmd_add(int argc, const char **argv, struct array *array)
{
    return ADD;
}

int cmd_rm(int argc, const char **argv, struct array *array)
{
    return RM;
}

int cmd_edit(int argc, const char **argv, struct array *array)
{
    return EDIT;
}

int cmd_ls(int argc, const char **argv, struct array *array)
{
    return LS;
}

int cmd_swap(int argc, const char **argv, struct array *array)
{
    return SWAP;
}

void log_msg(enum log_class log_class, const char *file, int lineno,
             const char *fmt, ...)
{
    return;
}

START_TEST(test_cmd_strarg)
{
    ck_assert_int_eq(strarg("0"), 0);
    ck_assert_int_eq(strarg("1"), 1);
    ck_assert_int_eq(strarg("100"), 100);
    ck_assert_int_eq(strarg(" 10 "), 10);
    ck_assert_int_eq(strarg("-1"), -1);
    ck_assert_int_eq(strarg("-10"), -10);
    ck_assert_int_eq(strarg("abcDEF"), -1);
    ck_assert_int_eq(strarg("abc200DEF400"), -1);
}
END_TEST

START_TEST(test_cmd_get)
{
    ck_assert_ptr_eq(get_cmd("add"), commands);
    ck_assert_ptr_eq(get_cmd("rm"), commands + 1);
    ck_assert_ptr_eq(get_cmd("edit"), commands + 2);
    ck_assert_ptr_eq(get_cmd("ls"), commands + 5);
    ck_assert_ptr_eq(get_cmd("swap"), commands + 8);
    ck_assert_ptr_null(get_cmd(""));
    ck_assert_ptr_null(get_cmd("notacommand"));
}
END_TEST

START_TEST(test_cmd_handle)
{
    int argc = 1;

    const char *argv_add[]     = { "add", NULL };
    const char *argv_rm[]      = { "rm", NULL };
    const char *argv_edit[]    = { "edit", NULL };
    const char *argv_ls[]      = { "ls", NULL };
    const char *argv_swap[]    = { "swap", NULL };
    const char *argv_default[] = { NULL };
    const char *argv_err[]     = { "notacommand", NULL };

    ck_assert_int_eq(handle_cmd(argc, argv_add, (struct array *)NULL), ADD);
    ck_assert_int_eq(handle_cmd(argc, argv_rm, (struct array *)NULL), RM);
    ck_assert_int_eq(handle_cmd(argc, argv_edit, (struct array *)NULL), EDIT);
    ck_assert_int_eq(handle_cmd(argc, argv_ls, (struct array *)NULL), LS);
    ck_assert_int_eq(handle_cmd(argc, argv_swap, (struct array *)NULL), SWAP);
    ck_assert_int_eq(handle_cmd(argc, argv_default, (struct array *)NULL), LS);
    ck_assert_int_eq(handle_cmd(argc, argv_err, (struct array *)NULL), ERR);
}
END_TEST

Suite *cmd_suite(void)
{
    Suite *s       = suite_create("cmd");
    TCase *tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_cmd_strarg);
    tcase_add_test(tc_core, test_cmd_get);
    tcase_add_test(tc_core, test_cmd_handle);
    suite_add_tcase(s, tc_core);

    return s;
}

int main()
{
    const TTest *tests[] = {
        test_cmd_strarg,
        test_cmd_get,
        test_cmd_handle,
        NULL,
    };

    return run_tests("cmd", tests, NULL, NULL);
}
