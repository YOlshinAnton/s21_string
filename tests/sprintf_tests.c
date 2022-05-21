START_TEST(test_s21_sprintf_char) {
    char s1[64]; *s1 = 0;
    char s2[64]; *s2 = 0;
    const char * formats[] = {
        "Plain text",
        "%c",
        "%10hhc",
        "%-20c",
        "plain text %-10c plain text #2",
        S21_NULL
    };
    for (int ch = 0; ch < 256; ch++) {
        for (int i = 0; formats[i]; ++i) {
            s21_size_t len1 = s21_sprintf(s1, formats[i], (int)ch);
            size_t len2 = sprintf(s2, formats[i], (int)ch);
            ck_assert_uint_eq(len1, len2);
            ck_assert_str_eq(s1, s2);
            ck_assert(strcmp(s1, s2) == 0);
        }
    }
}
END_TEST

START_TEST(test_s21_sprintf_string) {
    char s1[64]; *s1 = 0;
    char s2[64]; *s2 = 0;
    const char * str = "string";

    const char * formats[] = {
        "Plain text",
        "%s",
        "%10hhs",
        "%-20.2s",
        "plain text %-10s plain text #2",
        S21_NULL
    };

    s21_size_t tests_passed = 0;
    for (int i = 0; formats[i]; ++i) {
        s21_size_t len1 = s21_sprintf(s1, formats[i], str);
        size_t len2 = sprintf(s2, formats[i], str);
        ck_assert_uint_eq(len1, len2);
        ck_assert_str_eq(s1, s2);
        tests_passed++;
    }

    ck_assert_uint_eq(5, tests_passed);
}
END_TEST

START_TEST(test_s21_sprintf_int) {
    unsigned long long values[9] = {0, 0x8000, 0x4FFFFFFF, 0x7FFFFFFF,
                                0x80000000, 0x4FFFFFFFFFFFFFFF, 0x7FFFFFFFFFFFFFFF, 0x8000000000000000};

    char flags[7][4] = {"", "-", "+", " ", "-+", "+ -", "+- "};

    char spacing[6][3] = {"", "0", "1", "2", "5", "19"};

    char lengths[5][3] = {"h", "", "l", "hh", "ll"};

    char specifiers[3][2] = {"i", "d", "u"};

    char formatString[100];
    formatString[0] = '%';

    for (int specifierIndex = 0; specifierIndex < 3; specifierIndex++) {
        for (int lengthDescription = 0; lengthDescription < 5; lengthDescription++) {
            for (int widthDescription = 0; widthDescription < 6; widthDescription++) {
                for (int precisionDescription = 0; precisionDescription < 6; precisionDescription++) {
                    for (int valueIndex = 0; valueIndex < 8; valueIndex++) {
                        for (int flagsIndex = 0; flagsIndex < 7; flagsIndex++) {
                            formatString[1] = '\0';
                            s21_strcat(formatString, flags[flagsIndex]);
                            s21_strcat(formatString, spacing[widthDescription]);

                            if (precisionDescription != 0) {
                                s21_strcat(formatString, ".");
                            }

                            if (precisionDescription != 11) {
                                s21_strcat(formatString, spacing[precisionDescription]);
                            }

                            s21_strcat(formatString, lengths[lengthDescription]);
                            s21_strcat(formatString, specifiers[specifierIndex]);

                            char s21_str[100];
                            char str[100];

                            s21_sprintf(s21_str, formatString, values[valueIndex]);
                            sprintf(str, formatString, values[valueIndex]);

                            int eq = s21_strcmp(s21_str, str) == 0;

                            ck_assert(eq);
                        }
                    }
                }
            }
        }
    }
} END_TEST

START_TEST(test_s21_sprintf_float) {
    double values[] = {
        1.213612351234,
        .123401927309487102931203,
        123412351.000000132452345234522324235,
        120934.120934,
        222.007,
        3.14,
        -3.14,
        0.5, 1.5, 2.5, 3.5, 4.5,
        0.01, 1, 1.01, 2.01, 3.01, 0.001, 1.001, 2.001, 3.001,
        -0.0,
        -1.01,
        -0.00000000001,
        0.00000000001,
        .0000000000001,
        .0001,
        .00001,
        .0,
        1.1, 1.11, 1.12, 1.13, 1.14, 1.15, 1.16, 1.17, 1.18, 1.19,
        1.2,
        1.4, 4.011, 4.102, 4.130, 4.01040,
        1.5, 5.000001002003, 6.0009, 8.23400007,
        1.6, 1.7, 1.8, 1.9,
        91837490123.10293840001234,
        23.4,
        1.1799999999999999,
        INFINITY,
        0 - INFINITY,
        NAN
    };
    int values_count = sizeof(values) / sizeof(double);

    char flags[][4] = {"", "-", "+", " ", "-+", "+-", " -+", " +-", "+- "};
    int flags_count = sizeof(flags) / 4;

    char spacing[][3] = {"", "0", "1", "5", "6", "10", "15" };
    int spacing_count = sizeof(spacing) / 3;

    char lengths[][3] = {"", "l"};
    int lengths_count = sizeof(lengths) / 3;

    char formatString[100];
    formatString[0] = '%';

    for (int lengthDescription = 0; lengthDescription < lengths_count; lengthDescription++) {
    for (int valueIndex = 0; valueIndex < values_count; valueIndex++) {
    for (int widthDescription = 0; widthDescription < spacing_count; widthDescription++) {
    for (int precisionDescription = 0; precisionDescription < spacing_count; precisionDescription++) {
    for (int flagsIndex = 0; flagsIndex < flags_count; flagsIndex++) {
        formatString[1] = '\0';
        s21_strcat(formatString, flags[flagsIndex]);
        s21_strcat(formatString, spacing[widthDescription]);

        if (precisionDescription != 0) {
            s21_strcat(formatString, ".");
        }

        if (precisionDescription != 11) {
            s21_strcat(formatString, spacing[precisionDescription]);
        }

        s21_strcat(formatString, lengths[lengthDescription]);
        s21_strcat(formatString, "f");

        char s21_str[1000] = "";
        char str[1000] = "";

        s21_sprintf(s21_str, formatString, values[valueIndex]);
        sprintf(str, formatString, values[valueIndex]);

        ck_assert_str_eq(s21_str, str);
    }
    }
    }
    }
    }
} END_TEST


START_TEST(test_s21_sprintf_mixed) {
    char s21[512];
    char std[512];
    int s21_writen = s21_sprintf(s21, "%% %c %d %u %i %f %s", 'c', 123, 123u, 123, 0.001001093, "string");
    int std_writen = sprintf(std, "%% %c %d %u %i %f %s", 'c', 123, 123u, 123, 0.001001093, "string");
    ck_assert_int_eq(s21_writen, std_writen);
    ck_assert_str_eq(s21, std);
}
END_TEST

START_TEST(test__s21_sprintf__s21_ten_power) {
    ck_assert_int_eq(1, s21_ten_power(0));
    ck_assert_int_eq(10, s21_ten_power(1));
    ck_assert_int_eq(100, s21_ten_power(2));
    ck_assert_int_eq(1000, s21_ten_power(3));
}
END_TEST

START_TEST(test__s21_sprintf__s21_str_to_natural) {
    ck_assert_uint_eq(0, s21_str_to_natural("0", NULL));
    ck_assert_uint_eq(11, s21_str_to_natural("11", NULL));
    ck_assert_uint_eq(10, s21_str_to_natural("10", NULL));
    ck_assert_uint_eq(1192, s21_str_to_natural("1192", NULL));
}
END_TEST

START_TEST(test__s21_sprintf__s21_format_create) {
    s21_format_t format;

    format    = s21_format_create("-10s", 's');
    ck_assert_int_eq(1, format.left_align);
    ck_assert_int_eq(10, format.width);

    format = s21_format_create("+.0lf", 'f');
    ck_assert_int_eq(1, format.sign);
    ck_assert_int_eq(0, format.precision);
    ck_assert_int_eq(2, format.length);

    format = s21_format_create(" hd", 'd');
    ck_assert_int_eq(2, format.sign);
    ck_assert_int_eq(1, format.length);

    format = s21_format_create("-10c plain text #2", 'c');
    ck_assert_int_eq(1, format.left_align);
    ck_assert_int_eq(10, format.width);
}
END_TEST


/* additional */
START_TEST(sprintf_test) {
//  int a = 5;
//  int b;
//  int c;
//  char kstr1[100];
//  char kstr2[100];
//  char kstr3[350];
//  char kstr4[350];
//  char kstr5[350];
//  char kstr6[350];
//  char kstr7[350];
//  char kstr8[350];
//  s21_sprintf(kstr1, "Hello Andrew %d", 47);
//  sprintf(kstr2, "Hello Andrew %d", 47);
//  s21_sprintf(kstr3, "Hello World %d%c%s%i%g%o%u%x%X%p %e%E %n%f", 47, '\n',
//              "FAT32", 11, 22.6, 077, 9000000, 0x1F, 0x1F, &a, (double)6,
//              (double)6, &b, 14.22);
//  sprintf(kstr4, "Hello World %d%c%s%i%g%o%u%x%X%p %e%E %n%f", 47, '\n',
//          "FAT32", 11, 22.6, 077, (unsigned)9000000, 0x1F, 0x1F, &a, (double)6,
//          (double)6, &c, 14.22);
//  s21_sprintf(kstr5, "%-d %+d %0d % d %#o .5 %ld %hi", a, a, a, 56, 056,
//              (long)6000, (short)51);
//  sprintf(kstr7, "%.0f %20.4f", 3.5, 1234.1233);
//  s21_sprintf(kstr8, "%.0f %20.4f", 3.5, 1234.1233);
//  sprintf(kstr6, "%-d %+d %0d % d %#o .5 %ld %hi", a, a, a, 56, 056, (long)6000,
//          (short)51);
//  ck_assert_str_eq(kstr1, kstr2);
//  ck_assert_str_eq(kstr3, kstr4);
//  ck_assert_str_eq(kstr5, kstr6);
//  ck_assert_str_eq(kstr7, kstr8);
//  ck_assert_int_eq(s21_strlen(kstr1), s21_strlen(kstr2));
//  ck_assert_int_eq(s21_strlen(kstr3), s21_strlen(kstr4));
//  ck_assert_int_eq(s21_strlen(kstr5), s21_strlen(kstr6));
//  ck_assert_int_eq(b, c);
//
//  setlocale(LC_CTYPE, "");
//  char str1[1024];
//  char str2[1024];
//  char str3[1024];
//  char str4[1024];
//  char str5[1024];
//  char str6[1024];
//  ck_assert_int_eq(s21_sprintf(str1, "%*lc %020f", -20, L'異', 3.4),
//                   sprintf(str1, "%*C %020f", -20, L'異', 3.4));
//  ck_assert_int_eq(s21_sprintf(str2, "%-*.*ls %*.*ls", 20, 15, L"hello - 異   ",
//                               20, 15, L"hello - 異   "),
//                   sprintf(str2, "%-*.*ls %*.*ls", 20, 15, L"hello - 異   ", 20,
//                           15, L"hello - 異   "));
//  ck_assert_int_eq(s21_sprintf(str3, "%-*.*s", 20, 15, "Ku ku"),
//                   sprintf(str3, "%-*.*s", 20, 15, "Ku ku"));
//  ck_assert_int_eq(s21_sprintf(str4, "%+e %-+10g", 20.0, 15.),
//                   sprintf(str4, "%+e %-+10g", 20.0, 15.));
//  ck_assert_int_eq(s21_sprintf(str5, "%% %#x %0X %-20x %+f", 15, 16, 18, 15.4),
//                   sprintf(str5, "%% %#x %0X %-20x %+f", 15, 16, 18, 15.4));
//  ck_assert_int_eq(s21_sprintf(str6, "%+g %0g", 2.3, -5.6),
//                   sprintf(str6, "%+g %0g", 2.3, -5.6));
}
END_TEST
