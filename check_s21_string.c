#include "s21_string.h"
#include "s21_sprintf.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <check.h>

// part 1 tests
#include "tests/memory_manipulation_tests.c"
#include "tests/string_manipulation_tests.c"
#include "tests/string_examination_part1_tests.c"
#include "tests/string_examination_part2_tests.c"
#include "tests/strerror_tests.c"

// part 2 tests
#include "tests/sprintf_tests.c"

// part 5 tests
#include "tests/special_string_processing_tests.c"

// test suite
Suite * s21_string_suite(void) {
    Suite *s = suite_create("s21_string");
    /* cases */
    TCase *tc_memory_manipulation = tcase_create("memoty manipulation");
    TCase *tc_string_manipulation = tcase_create("string manipulation");
    TCase *tc_string_examination1 = tcase_create("string examination 1");
    TCase *tc_string_examination2 = tcase_create("string examination 2");
    TCase *tc_strerror = tcase_create("strerror");
    TCase *tc_sprintf = tcase_create("sprintf");
    TCase *tc_special = tcase_create("special");

        /* case: memory manipulation */
        tcase_add_test(tc_memory_manipulation, test_s21_memset);
        tcase_add_test(tc_memory_manipulation, test_s21_memmove);
        tcase_add_test(tc_memory_manipulation, test_s21_memcmp);
        tcase_add_test(tc_memory_manipulation, test_s21_memcpy);
        tcase_add_test(tc_memory_manipulation, test_s21_memchr);

        /* case: string manipulation */
        tcase_add_test(tc_string_manipulation, test_s21_strcat);
        tcase_add_test(tc_string_manipulation, test_s21_strncat);
        tcase_add_test(tc_string_manipulation, test_s21_strcpy);
        tcase_add_test(tc_string_manipulation, test_s21_strncpy);

        /* case: string examination 1 */
        tcase_add_test(tc_string_examination1, test_s21_strlen);
        tcase_add_test(tc_string_examination1, test_s21_strcmp);
        tcase_add_test(tc_string_examination1, test_s21_strncmp);
        tcase_add_test(tc_string_examination1, test_s21_strchr);
        tcase_add_test(tc_string_examination1, test_s21_strrchr);

        /* case: string examination 2 */
        tcase_add_test(tc_string_examination2, test_s21_strspn);
        tcase_add_test(tc_string_examination2, test_s21_strcspn);
        tcase_add_test(tc_string_examination2, test_s21_strpbrk);
        tcase_add_test(tc_string_examination2, test_s21_strstr);
        tcase_add_test(tc_string_examination2, test_s21_strtok);

        /* case: s21_strerror */
        tcase_add_test(tc_strerror, test_s21_strerror);

        /* case: s21_sprintf */
        tcase_add_test(tc_sprintf, test__s21_sprintf__s21_ten_power);
        tcase_add_test(tc_sprintf, test__s21_sprintf__s21_str_to_natural);
        tcase_add_test(tc_sprintf, test__s21_sprintf__s21_format_create);
        tcase_add_test(tc_sprintf, test_s21_sprintf_char);
        tcase_add_test(tc_sprintf, test_s21_sprintf_string);
        tcase_add_test(tc_sprintf, test_s21_sprintf_int);
        tcase_add_test(tc_sprintf, test_s21_sprintf_float);
        tcase_add_test(tc_sprintf, test_s21_sprintf_mixed);
        tcase_add_test(tc_sprintf, sprintf_test);

        /* case: special */
        tcase_add_test(tc_special, test_s21_to_upper);
        tcase_add_test(tc_special, test_s21_to_lower);
        tcase_add_test(tc_special, test_s21_insert);
        tcase_add_test(tc_special, test_s21_trim);

    /* suite */
    suite_add_tcase(s, tc_memory_manipulation);
    suite_add_tcase(s, tc_string_manipulation);
    suite_add_tcase(s, tc_string_examination1);
    suite_add_tcase(s, tc_string_examination2);
    suite_add_tcase(s, tc_strerror);
    suite_add_tcase(s, tc_sprintf);
    suite_add_tcase(s, tc_special);

    return s;
}

int main() {
    int number_failed;
    Suite    *s = s21_string_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
