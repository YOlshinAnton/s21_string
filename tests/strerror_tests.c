START_TEST(test_s21_strerror) {
    for (int i = -1; i < 200; i++) {
        int eq = strcmp(s21_strerror(i), strerror(i)) == 0;
        ck_assert(eq);
    }
}
END_TEST
