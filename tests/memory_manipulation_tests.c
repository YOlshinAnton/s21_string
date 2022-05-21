START_TEST(test_s21_memchr) {
    char *str0 = "";
    char *str1 = "a";
    char *str2 = "c";
    char *str3 = "aaaa";
    char *str4 = "aaac";
    char *str5 = "caca";
    char *str6 = "aaacaa";
    char *str7 = "aaacaac";

    ck_assert(s21_memchr(str0, '\0', 0) == memchr(str0, '\0', 0));
    ck_assert(s21_memchr(str0, '\0', 1) == memchr(str0, '\0', 1));  // segfault? undefined?
    ck_assert(s21_memchr(str0, 'c', 0) == memchr(str0, 'c', 0));
    ck_assert(s21_memchr(str0, 'c', 1) == memchr(str0, 'c', 1));  // segfault? undefined?

    ck_assert(s21_memchr(str1, 'c', 0) == memchr(str1, 'c', 0));
    ck_assert(s21_memchr(str1, 'c', 1) == memchr(str1, 'c', 1));

    ck_assert(s21_memchr(str2, 'c', 0) == memchr(str2, 'c', 0));
    ck_assert(s21_memchr(str2, 'c', 1) == memchr(str2, 'c', 1));

    ck_assert(s21_memchr(str3, 'c', 1) == memchr(str3, 'c', 1));
    ck_assert(s21_memchr(str3, 'c', 4) == memchr(str3, 'c', 4));

    ck_assert(s21_memchr(str4, 'c', 1) == memchr(str4, 'c', 1));
    ck_assert(s21_memchr(str4, 'c', 3) == memchr(str4, 'c', 3));
    ck_assert(s21_memchr(str4, 'c', 4) == memchr(str4, 'c', 4));

    ck_assert(s21_memchr(str5, 'c', 0) == memchr(str5, 'c', 0));
    ck_assert(s21_memchr(str5, 'c', 1) == memchr(str5, 'c', 1));
    ck_assert(s21_memchr(str5, 'c', 3) == memchr(str5, 'c', 3));
    ck_assert(s21_memchr(str5, 'c', 4) == memchr(str5, 'c', 4));

    ck_assert(s21_memchr(str6, 'c', 3) == memchr(str6, 'c', 3));
    ck_assert(s21_memchr(str6, 'c', 4) == memchr(str6, 'c', 4));
    ck_assert(s21_memchr(str6, 'c', 6) == memchr(str6, 'c', 6));

    ck_assert(s21_memchr(str7, 'c', 3) == memchr(str7, 'c', 3));
    ck_assert(s21_memchr(str7, 'c', 4) == memchr(str7, 'c', 4));
    ck_assert(s21_memchr(str7, 'c', 7) == memchr(str7, 'c', 7));

    // Third parameter must be s21_size_t. There is no test for that.
} END_TEST

START_TEST(test_s21_memcmp) {
    int a, b;

    char * examples[] = {
        "",
        "a",
        "ab",
        "ba",
        "asdfasodhfa;sldjlkajwipoehrqwo123-y09751",
        "Camus"
    };
    const s21_size_t examples_count = sizeof(examples) / sizeof(char*);

    for (s21_size_t i = 0; i < examples_count; ++i) {
        for (s21_size_t j = 0; j < examples_count; ++j) {
            for (s21_size_t n = 0; n < s21_strlen(examples[i]); ++n) {
                a = s21_memcmp(examples[i], examples[j], n);
                b = memcmp(examples[i], examples[j], n);
                ck_assert(a == b || (a > 0 && b > 0) || (a < 0 && b < 0));
            }
        }
    }
} END_TEST

START_TEST(test_s21_memset) {
    char s21_str[10];
    char str[10];

    s21_memset(s21_str, 'a', 9);
    memset(str, 'a', 9);

    s21_str[9] = '\0';
    str[9] = '\0';

    ck_assert(s21_memcmp(s21_str, str, 10) == 0);

    memset(s21_str, 'a', 9);
    memset(str, 'a', 9);

    s21_str[9] = '\0';
    str[9] = '\0';

    s21_memset(s21_str, 'c', 4);
    memset(str, 'c', 4);

    ck_assert(s21_memcmp(s21_str, str, 10) == 0);
} END_TEST

START_TEST(test_s21_memcpy) {
    char s21_str[10];
    char str[10];

    s21_memset(s21_str, 'a', 9);
    s21_memset(str, 'a', 9);

    s21_str[9] = '\0';
    str[9] = '\0';

    s21_memcpy(s21_str, "bcde", 4);
    s21_memcpy(str, "bcde", 4);

    ck_assert(s21_memcmp(s21_str, str, 10) == 0);

    s21_memset(s21_str, 'a', 9);
    s21_memset(str, 'a', 9);

    s21_str[9] = '\0';
    str[9] = '\0';

    s21_memcpy(s21_str, "bcdebcdeb", 4);
    s21_memcpy(str, "bcdebcdeb", 4);

    ck_assert(s21_memcmp(s21_str, str, 10) == 0);

    s21_memset(s21_str, 'a', 9);
    s21_memset(str, 'a', 9);

    s21_str[9] = '\0';
    str[9] = '\0';

    s21_memcpy(s21_str, "bcdebcdeb", 9);
    s21_memcpy(str, "bcdebcdeb", 9);

    ck_assert(s21_memcmp(s21_str, str, 10) == 0);
} END_TEST

START_TEST(test_s21_memmove) {
    char s21_str[10];
    char str[10];

    for (int i = 0; i < 9; i++) {
        s21_str[i] = '0' + i;
        str[i] = '0' + i;
    }

    s21_str[9] = '\0';
    str[9] = '\0';

    s21_memmove(s21_str + 1, s21_str, 4);
    memmove(str + 1, str, 4);

    ck_assert(s21_memcmp(s21_str, str, 10) == 0);

    for (int i = 0; i < 9; i++) {
        s21_str[i] = '0' + i;
        str[i] = '0' + i;
    }

    s21_str[9] = '\0';
    str[9] = '\0';

    s21_memmove(s21_str + 1, s21_str, 8);
    memmove(str + 1, str, 8);

    ck_assert(s21_memcmp(s21_str, str, 10) == 0);
} END_TEST
