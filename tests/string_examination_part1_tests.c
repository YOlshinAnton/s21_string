START_TEST(test_s21_strlen) {
    char * str1 = "";
    char * str2 = "Violets";

    ck_assert(s21_strlen(str1) == strlen(str1));
    ck_assert(s21_strlen(str2) == strlen(str2));
}
END_TEST

START_TEST(test_s21_strcmp) {
    char * s1 = "";
    char * s2 = "Violets";
    char * s3 = "violets";

    ck_assert(s21_strcmp(s1, s2) == strcmp(s1, s2));
    ck_assert(s21_strcmp(s2, s1) == strcmp(s2, s1));
    ck_assert(s21_strcmp(s2, s3) == strcmp(s2, s3));
    ck_assert(s21_strcmp(s3, s2) == strcmp(s3, s2));
}
END_TEST

START_TEST(test_s21_strncmp) {
    char * s1 = "";
    char * s2 = "Violets";
    char * s3 = "violets";

    ck_assert(s21_strncmp(s1, s2, 5) == strncmp(s1, s2, 5));
    ck_assert(s21_strncmp(s2, s1, 1) == strncmp(s2, s1, 1));
    ck_assert(s21_strncmp(s2, s3, 1) == strncmp(s2, s3, 1));
    ck_assert(s21_strncmp(s3, s2, 1) == strncmp(s3, s2, 1));
}
END_TEST

START_TEST(test_s21_strchr) {
    const char * strings[] = {
        "string STRING Hundreds of cigarets \n",
        "\n\t\0",
    };
    s21_size_t n = sizeof(strings) / sizeof(char*);
    for (s21_size_t i = 0; i < n; ++i) {
        const char * example = strings[i];
        for (int c = 0; c < 255; ++c) {
            char *s21 = s21_strchr(example, c);
            char *std = strchr(example, c);
            ck_assert(s21 == std);
        }
    }
}
END_TEST

START_TEST(test_s21_strrchr) {
    const char * strings[] = {
        "string",
        "STRING",
        "",
        "\n\t\0",
    };
    s21_size_t strings_count = sizeof(strings) / sizeof(char*);
    for (s21_size_t i = 0; i < strings_count; ++i) {
        for (int c = 0; c < 256; ++c) {
            char * s21 = s21_strrchr(strings[i], c);
            char * std = strrchr(strings[i], c);
            ck_assert(s21 == std);
        }
    }
}
END_TEST
