START_TEST(test_s21_strcpy) {
    char s1[64] = "Vio";
    char s2[64] = "Violeta";
    ck_assert(strcmp(s21_strcpy(s1, s2), strcpy(s1, s2)) == 0);
    ck_assert(strcmp(s21_strcpy(s2, s1), strcpy(s2, s1)) == 0);
}
END_TEST

START_TEST(test_s21_strncpy) {
    char s1[64] = "Vio";
    char s2[64] = "Violeta";

    ck_assert(strcmp(s21_strncpy(s1, s2, 3), strncpy(s1, s2, 3)) == 0);
    ck_assert(strcmp(s21_strncpy(s2, s1, 3), strncpy(s2, s1, 3)) == 0);
}
END_TEST

START_TEST(test_s21_strcat) {
    char s1[64] = "Vio";

    char s21[128]; s21[0] = 0; s21_strcat(s21, s1);
    char std[128]; std[0] = 0; strcat(std, s1);

    ck_assert_str_eq(s21, std);
}
END_TEST

START_TEST(test_s21_strncat) {
    char s1[64] = "Vio";
    char s2[64] = "Violeta";
    char s3[64] = "";

    ck_assert(strcmp(s21_strncat(s1, s2, 3), strncat(s1, s2, 3)) == 0);
    ck_assert(strcmp(s21_strncat(s2, s1, 3), strncat(s2, s1, 3)) == 0);
    ck_assert(strcmp(s21_strncat(s2, s1, 0), strncat(s2, s1, 0)) == 0);
    ck_assert(strcmp(s21_strncat(s1, s2, 0), strncat(s1, s2, 0)) == 0);
    ck_assert(strcmp(s21_strncat(s2, s3, 3), strncat(s2, s3, 3)) == 0);
    ck_assert(strcmp(s21_strncat(s3, s2, 3), strncat(s3, s2, 3)) == 0);
    ck_assert(strcmp(s21_strncat(s2, s3, 0), strncat(s2, s3, 0)) == 0);
    ck_assert(strcmp(s21_strncat(s3, s2, 0), strncat(s3, s2, 0)) == 0);
}
END_TEST
