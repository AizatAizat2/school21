#include "s21_string.h"

#include <stdio.h>
#include <check.h>
#include <string.h>
#include <stdlib.h>

START_TEST(test_strlen) {
    extern my_size_t s21_strlen(const char *str);
    const char *ch = "Og Buda pozhalusta poshadi";
    int my_str = s21_strlen(ch);
    int dont_my_str = strlen(ch);

    ck_assert_uint_eq(strlen(ch), s21_strlen(ch));
    printf(" [PASS] Test: s21_strlen: %d. strlen: %d.", my_str, dont_my_str);
}
END_TEST




Suite *s21_string_suite(void) {
    Suite *s;
    TCase *strlen_core;
    // suda potom ebash eshe che nado

    s = suite_create("strlen_test");
    strlen_core = tcase_create("Core");
    // i suda tozhe samoe

    tcase_add_test(strlen_core, test_strlen);
    suite_add_tcase(s, strlen_core);

    return s;
}

int main() {
    Suite *suite = s21_string_suite();
    SRunner *runner = srunner_create(suite);
    
    srunner_run_all(runner, CK_NORMAL);
    // int no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return 0;
}