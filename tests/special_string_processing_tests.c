START_TEST(test_s21_to_upper) {
    char * formats[][2] = {
        { "Plain text", "PLAIN TEXT" },
        { "", "" },
        { S21_NULL, S21_NULL }
    };
    for (int i = 0; formats[i][0]; ++i) {
        char * in = formats[i][0];
        char * out = s21_to_upper(in);
        char * expectation = formats[i][1];

        ck_assert_str_eq(out, expectation);

        if (out) free(out);
    }
}
END_TEST

START_TEST(test_s21_to_lower) {
    char * formats[][2] = {
        { "Plain Text", "plain text" },
        { "LOUD" , "loud" },
        { "", "" },
        { S21_NULL, S21_NULL }
    };
    for (int i = 0; formats[i][0]; ++i) {
        char * in = formats[i][0];
        char * out = s21_to_lower(in);
        char * expectation = formats[i][1];

        ck_assert_str_eq(out, expectation);

        if (out) free(out);
    }
}
END_TEST

START_TEST(test_s21_insert) {
    char * in1appolo = "A seven-foot frame\n Rats along his back\n";
    char * in1athena = "When he calls your name\n It all fades to balck\n";
    char * expectation1 =
    "A seven-foot frame\n Rats along his back\n"
    "When he calls your name\n It all fades to balck\n";
    s21_size_t index1 = strlen(in1appolo);
    char * out1 = s21_insert(in1appolo, in1athena, index1);
    ck_assert_str_eq(out1, expectation1);
    free(out1);

    char * in2Hilber = "H";
    char * in2Born = "B";
    char * expectation2HB = "HB";
    char * expectation2BH = "BH";
    char * out2HB = s21_insert(in2Hilber, in2Born, 1);
    char * out2BH = s21_insert(in2Hilber, in2Born, 0);
    ck_assert_str_eq(expectation2HB, out2HB);
    ck_assert_str_eq(expectation2BH, out2BH);
    free(out2HB);
    free(out2BH);
}
END_TEST

START_TEST(test_s21_trim) {
    char * where1 = "ssssassss";
    char * where2 = "sssssssss";
    char * where3 = "";
    char * where4 = "sssaaasaasasss";

    char * what = "s";
    char * out1 = s21_trim(where1, what);
    char * out2 = s21_trim(where2, what);
    char * out3 = s21_trim(where3, what);
    char * out4 = s21_trim(where4, what);

    ck_assert_str_eq("a", out1);
    ck_assert_str_eq("", out2);
    ck_assert_str_eq(where3, out3);
    ck_assert_str_eq("aaasaasa", out4);

    free(out1);
    free(out2);
    free(out3);
    free(out4);
}
END_TEST
