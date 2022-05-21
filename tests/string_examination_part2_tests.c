START_TEST(test_s21_strspn) {
    const char * s1 = "Handreds of cigarettes had been smoked in that house.";
    const char * c1 = "abcdefghijklmnopqrstubwxyzH";
    const char * c2 = "ed";
    const char * c3 = "";

    ck_assert(s21_strspn(s1, c1) == strspn(s1, c1));
    ck_assert(s21_strspn(s1, c1) == strspn(s1, c1));
    ck_assert(s21_strspn(s1, c2) == strspn(s1, c2));
    ck_assert(s21_strspn(s1, c3) == strspn(s1, c3));
}
END_TEST

START_TEST(test_s21_strcspn) {
    const char * s1 = "Handred of cigarettes had been smiked in that house.";
    const char * c1 = "abcdefghijklmnopqrstubwxyzH";
    const char * c2 = "ed";
    const char * c3 = "";

    ck_assert(s21_strcspn(s1, c1) == strcspn(s1, c1));
    ck_assert(s21_strcspn(s1, c2) == strcspn(s1, c2));
    ck_assert(s21_strcspn(s1, c3) == strcspn(s1, c3));
}
END_TEST

START_TEST(test_s21_strpbrk) {
    const char * s1 = "Handred of cigarettes had been smiked in that house.";
    const char * c1 = "abcdefghijklmnopqrstubwxyz";
    const char * c2 = "h";
    const char * c3 = "";

    ck_assert(s21_strpbrk(s1, c1) == strpbrk(s1, c1));
    ck_assert(s21_strpbrk(s1, c2) == strpbrk(s1, c2));
    ck_assert(s21_strpbrk(s1, c3) == strpbrk(s1, c3));
}
END_TEST

START_TEST(test_s21_strstr) {
    const char * s1 = "Handred of cigarettes had been smiked in that house.";
    const char * s2 = "";
    const char * s3 = "cigarettes";

    ck_assert(s21_strstr(s1, s2) == strstr(s1, s2));
    ck_assert(s21_strstr(s1, s3) == strstr(s1, s3));
    ck_assert(s21_strstr(s2, s2) == strstr(s2, s2));
    ck_assert(s21_strstr(s2, s3) == strstr(s2, s3));
}
END_TEST

START_TEST(test_s21_strtok) {
    char s1[64]; strcpy(s1, "one + two * (three - four)!");
    char s2[64]; strcpy(s2, "one + two * (three - four)!");
    const char * d1 = "! +- (*)";
    char * sp1;
    char * sp2;

    /* cppcheck
    sp1 = s21_strtok(S21_NULL, S21_NULL);
    sp2 = strtok(NULL, NULL);
    ck_assert( sp1 == sp2 );
     */

    sp1 = s21_strtok(s1, d1);
    sp2 = strtok(s2, d1);
    ck_assert_str_eq(sp1, sp2);

    sp1 = s21_strtok(S21_NULL, d1);
    sp2 = strtok(NULL, d1);
    ck_assert_str_eq(sp1, sp2);

    sp1 = s21_strtok(S21_NULL, d1);
    sp2 = strtok(NULL, d1);
    ck_assert_str_eq(sp1, sp2);

    sp1 = s21_strtok(s1, d1);
    sp2 = strtok(s2, d1);
    ck_assert_str_eq(sp1, sp2);

    /* cppcheck
    sp1 = s21_strtok(S21_NULL, S21_NULL);
    sp2 = strtok(NULL, NULL);
    ck_assert( sp1 == sp2 );
    */
}
END_TEST
