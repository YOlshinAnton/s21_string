#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_

#include <stdarg.h>

long s21_ten_power(unsigned int x);
s21_size_t s21_str_to_natural(const char * str, char **sendp);

typedef struct s21_format {
    int blank;
    int left_align;  // flag - (default 0)
    int sign;        // flag + (default 0)
    int width;       // ex. %10c
    int precision;   // ex. %.4f (default -1 - not specified)
    int length;      // 1 - short, 2 - long
} s21_format_t;

s21_format_t s21_format_create(const char * frm, char spc);

#endif  // SRC_S21_SPRINTF_H_
