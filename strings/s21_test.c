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
    printf(" [PASS] Test: s21_strlen: %d. strlen: %d.\n", my_str, dont_my_str);
}
END_TEST

START_TEST(test_memchr) {
    extern void *memchr(const void *str, int c, my_size_t n);
    const void *str = "Suka vernite dengi sudebnie pristavi";
    int c = 'd';
    my_size_t n = strlen(str);
    void *ch_s21_memchr = s21_memchr(str, c, n);
    void *ch_memchr = memchr(str, c, n);

    ck_assert_ptr_eq(memchr(str, c, n), s21_memchr(str, c, n));
    printf(" [PASS] Test: s21_memchr: %p. memchr: %p.\n", ch_s21_memchr, ch_memchr);
}
END_TEST

START_TEST(test_memcmp) {
    extern int s21_mecmp(const void *str1, const void *str2, my_size_t n);
    const void *str1 = "Sberbank dai deneg pz";  // \0 == 0
    const void *str2 = "Sberbank dai deneg pz suki pidarasi"; // space == 32. 0 - 32 = -32.

    my_size_t n = strlen(str2);
    int result_s21_mecmp = s21_memcmp(str1, str2, n);
    int result_memcmp = memcmp(str1, str2, n);

    ck_assert_uint_eq(memcmp(str1, str2, n), s21_memcmp(str1, str2, n));
    printf(" [PASS] Test: s21_memcmp: %d. memcmp: %d.\n", result_s21_mecmp, result_memcmp);
}
END_TEST

START_TEST(test_memcpy) {

    extern void *s21_memcpy(void *dest, const void *src, my_size_t n);
    void* dest[10];
    const void *src = "suka";

    my_size_t n = strlen(src);

    void *result_s21_memcpy = s21_memcpy(dest, src, n);
    void *result_memcpy = memcpy(dest, src, n);

    ck_assert_ptr_eq(s21_memcpy(dest, src, n), memcpy(dest, src, n));
    printf(" [PASS] Test: s21_memcpy: %p. memcpy: %p.\n", result_s21_memcpy, result_memcpy);

}
END_TEST

Suite *s21_string_suite(void) {
    Suite *s;
    TCase *s21_strlen, *s21_memchr, *s21_memcmp, *s21_memcpy;

    s = suite_create("str_tests");

    s21_strlen = tcase_create("strlen");
    tcase_add_test(s21_strlen, test_strlen);
    suite_add_tcase(s, s21_strlen);

    s21_memchr = tcase_create("memchr");
    tcase_add_test(s21_memchr, test_memchr);
    suite_add_tcase(s, s21_memchr);

    s21_memcmp = tcase_create("memcmp");
    tcase_add_test(s21_memcmp, test_memcmp);
    suite_add_tcase(s, s21_memcmp);

    s21_memcpy = tcase_create("memcpy");
    tcase_add_test(s21_memcpy, test_memcpy);
    suite_add_tcase(s, s21_memcpy);

    return s;
}

int main() {
    int failed = 0;
    Suite *s;
    SRunner *runner;

    s = s21_string_suite();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}