#include "s21_string.h"
#include "s21_sprintf.h"
#include <stdlib.h>

static s21_size_t swrite_formatted(char * str, const char * frm, char spc, va_list * argp);
static s21_size_t swrite_char(char * str, s21_format_t format, va_list * argp);
static s21_size_t swrite_string(char * str, s21_format_t format, va_list * argp);
static s21_size_t swrite_decimal(char * str, s21_format_t format, va_list * argp);
static s21_size_t swrite_unsigned(char * str, s21_format_t format, va_list * argp);
static s21_size_t swrite_float(char * str, s21_format_t format, va_list * argp);

static void reverseString(char *str, int n) {
    n--;

    for (int i = 0; i < n - i; i++) {
        char temp = str[i];
        str[i] = str[n - i];
        str[n - i] = temp;
    }
}

static void alignText(char *str, int leftJustify, s21_size_t *shift, s21_size_t amountOfChars, int blank) {
    if (leftJustify) {
        while (*shift < amountOfChars) {
            str[*shift] = blank;
            (*shift)++;
        }
    } else {
        if (*shift < amountOfChars) {
            int n = amountOfChars - *shift;
            int curr = *shift;

            do {
                curr--;
                str[curr + n] = str[curr];
            } while (curr > 0);

            s21_memset(str, blank, n);
            *shift = amountOfChars;
        }
    }
}

static int is_digit(int c) {
    return 48 <= c && c <= 57;
}

long s21_ten_power(unsigned int x) {
    long product = 1;
    if (x == 0) {
        product = 1;
    } else {
        do { product *= 10; } while (--x);
    }
    return product;
}

s21_size_t s21_str_to_natural(const char * str, char **sendp) {
    s21_size_t number = 0;
    if (*str != '0') {
        s21_size_t digits = 0;
        while (*str && (48 <= * str && *str <= 57)) {
            ++str; ++digits;
        }
        if (sendp) *sendp = (char*)str;
        str -= digits;
        while (*str && (48 <= * str && *str <= 57)) {
            int digit = (int)(*str - 48);
            number += s21_ten_power(--digits) * digit;
            ++str;
        }
    }
    return number;
}

s21_format_t s21_format_create(const char * frm, char spc) {
    s21_format_t format = {
        .blank = ' ',
        .left_align = 0,
        .sign = 0,
        .width = 0,
        .precision = -1,
        .length = 0
    };

    char ** frmp = (char**) &frm;
    while (*frm && *frm != spc) {
        int l = format.length;
        switch (*frm) {
            case '0': format.blank = format.left_align == 0 ? (int) '0' : format.blank;
                      break;
            case '-': format.left_align = 1;
                      format.blank = (int) ' ';
                      break;
            case '+': format.sign = 1;
                      break;
            case ' ': format.sign = (format.sign == 1 ? 1 : 2);
                      break;
            case '.':
                      ++frm;
                      if (is_digit(*(frm))) {
                          format.precision = (int) s21_str_to_natural(frm, frmp); frm = *frmp;
                          if (format.precision) --frm;
                      } else {
                          format.precision = 0;
                          --frm;
                      }
                      break;
            case '1': case '2': case '3':
            case '4': case '5': case '6':
            case '7': case '8': case '9':
                      format.width = (int) s21_str_to_natural(frm, frmp); frm = *frmp;
                      --frm;
                      break;
            /* */
            case 'h':
                format.length = (l == 0) + (l == 1) * 3 + (l != 0 && l != 1) * l;
                break;
            case 'l':
                format.length = (l == 0 || l == 1 || l == 3) * 2 + (l == 2) * 4;
                break;
            default: break;
        }
        ++frm;
    }

    return format;
}

int s21_sprintf(char * restrict str, const char * restrict format, ...) {
    const char * specifiers = "cdifsu%";

    va_list args;
    va_start(args, format);

    *str = 0;
    s21_size_t writen_len = 0;
    while (*format) {
        s21_size_t segment_len = 0;
        s21_size_t formatted_len = 0;

        /* write plain text segment */
        segment_len = s21_strcspn(format, "%");
        s21_strncpy(str, format, segment_len);
        str += segment_len;
        format += segment_len;
        writen_len += segment_len;

        if (*format == '%') ++format;

        /* write format segment */
        if (*format) {
            char specifier;
            segment_len = s21_strcspn(format, specifiers);
            specifier = *(format + segment_len);
            formatted_len = swrite_formatted(str, format, specifier, &args);
            str += formatted_len;
            format += segment_len + 1;
        }
        writen_len += formatted_len;
    }
    *str = 0;
    va_end(args);
    return writen_len;
}

static s21_size_t swrite_formatted(char * str, const char * frm, char spc, va_list * argp) {
    s21_format_t format = s21_format_create(frm, spc);
    s21_size_t writen_count = 0;
    switch (spc) {
        case 'c': writen_count = swrite_char(str, format, argp); break;
        case 's': writen_count = swrite_string(str, format, argp); break;
        case 'i':
        case 'd': writen_count = swrite_decimal(str, format, argp); break;
        case 'u': writen_count = swrite_unsigned(str, format, argp); break;
        case 'f': writen_count = swrite_float(str, format, argp); break;
        case '%': writen_count = 1; *str = '%'; break;
    }
    return writen_count;
}

static s21_size_t swrite_char(char * str, s21_format_t format, va_list * argp) {
    int c = va_arg(*argp, int);

    s21_size_t width = format.width ? format.width : 1;
    s21_size_t written = width;

    if (format.left_align == 0) {
        *(str + width - 1) = c;
    } else {
        *str = c;
        ++str;
    }
    while (--width) {
        *(str++) = ' ';
    }
    return written;
}

static s21_size_t swrite_string(char * str, s21_format_t format, va_list * argp) {
    char * s = va_arg(*argp, char*);
    s21_size_t precision = (format.precision == -1 ? 0 : format.precision);
    s21_size_t len = precision == 0 ? s21_strlen(s) : precision;
    s21_size_t width = (s21_size_t)format.width >= len ? format.width - len: 0;
    s21_size_t written = len + width;
    if (format.left_align == 0) {
        while (width) {
            *str++ = ' ';
            width--;
        }
        for (s21_size_t i = 0; i < len; ++i)
            *str++ = *(s + i);
    } else {
        for (s21_size_t i = 0; i < len; ++i)
            *str++ = *(s + i);
        while (width) {
            *str++ = ' ';
            width--;
        }
    }
    return written;
}

static s21_size_t swrite_decimal(char * str, s21_format_t format, va_list * argp) {
    long long value;
    switch (format.length) {
        case 0:
            value = (int)va_arg(*argp, int);
            break;
        case 1:
            value = (short)va_arg(*argp, int);
            break;
        case 2:
            value = (long)va_arg(*argp, long);
            break;
        case 3:
            value = (char)va_arg(*argp, int);
            break;
        default:
            value = (long long)va_arg(*argp, long long);
    }

    int additionalChar = 0;

    if (value < 0) {
        *str = '-';
        additionalChar = 1;
    } else {
        if (format.sign == 1) {
            *str = '+';
            additionalChar = 1;
        } else if (format.sign == 2) {
            *str = ' ';
            additionalChar = 1;
        }
    }

    s21_size_t shift = 0;

    while (value != 0) {
        int digit = value % 10;

        if (digit < 0) {
            digit *= -1;  // There is no positive pair for minimal int (example: -128 .. 127)
        }

        str[additionalChar + shift] = '0' + digit;
        value /= 10;
        shift++;
    }

    unsigned int amountOfDigits = format.precision == -1 ? 1 : format.precision;

    while (shift < amountOfDigits) {
        str[additionalChar + shift] = '0';
        shift++;
    }

    reverseString(str + additionalChar, shift);

    shift += additionalChar;

    alignText(str, format.left_align, &shift, format.width, format.blank);

    return shift;
}

static s21_size_t swrite_unsigned(char * str, s21_format_t format, va_list * argp) {
    unsigned long long value;
    switch (format.length) {
        case 0:
            value = (unsigned)va_arg(*argp, unsigned);
            break;
        case 1:
            value = (unsigned short)va_arg(*argp, unsigned int);
            break;
        case 2:
            value = (unsigned long)va_arg(*argp, unsigned long);
            break;
        case 3:
            value = (unsigned char)va_arg(*argp, unsigned int);
            break;
        default:
            value = (unsigned long long)va_arg(*argp, unsigned long long);
    }

    s21_size_t shift = 0;

    while (value != 0) {
        int digit = value % 10;

        str[shift] = '0' + digit;
        value /= 10;
        shift++;
    }

    unsigned int amountOfDigits = format.precision == -1 ? 1 : format.precision;

    while (shift < amountOfDigits) {
        str[shift] = '0';
        shift++;
    }

    reverseString(str, shift);

    alignText(str, format.left_align, &shift, format.width, format.blank);

    return shift;
}

static s21_size_t swrite_float(char * str, s21_format_t format, va_list *argp) {
    double zq = va_arg(*argp, double);
    long double q = (long double) zq;

    long precision = format.precision == -1 ? 6 : format.precision;

    /* exceptions */
    unsigned long long llq; (s21_memcpy(&llq, &zq, sizeof(double)));
    // infinity
    unsigned long long llinf = 0x7FF0000000000000;
    unsigned long long llninf = 0xFFF0000000000000;
    int is_infinity = llinf == llq;
    int is_negative_infinity = llninf == llq;
    // negative nan
    unsigned long long llnegnan_max = 0xFFFFFFFFFFFFFFFFull;
    unsigned long long llnegnan_min = 0xFFF0000000000001ull;
    int is_negative_nan = llnegnan_min <= llq && llq <= llnegnan_max;
    // nan
    unsigned long long llnan_max = 0x7FFFFFFFFFFFFFFFull;
    unsigned long long llnan_min = 0x7FF0000000000001ull;
    int is_nan = (llnan_min <= llq && llq <= llnan_max) || is_negative_nan;
    // negative zero
    double nz = -0.0;
    unsigned long long llnz; (s21_memcpy(&llnz, &nz, sizeof(double)));
    int is_negative_zero = llnz == llq;
    /* exceptions */

    int is_negative =  q < 0 || is_negative_zero || is_negative_nan;
    if (is_negative) q *= -1;

    char int_part_string[32] = "";
    char flt_part_string[32] = "";
    int sign_space = 0;

#ifdef __APPLE__
    if (!is_nan) {
#endif
        if (is_negative) {
            int_part_string[0] = '-'; sign_space = 1;
        } else if (format.sign == 1) {
            int_part_string[0] = '+'; sign_space = 1;
        } else if (format.sign == 2) {
            int_part_string[0] = ' '; sign_space = 1;
        }
#ifdef __APPLE__
    }
#endif
    if (is_infinity || is_negative_infinity || is_nan) {
        if (is_negative_infinity || is_infinity) {
            s21_strcpy(int_part_string + sign_space, "inf");
        } else {
            if (is_negative_nan) {
                s21_strcpy(int_part_string + sign_space, "-nan");
            } else {
                s21_strcpy(int_part_string + sign_space, "nan");
            }
        }
        flt_part_string[0] = 0;
    } else {
        // integer
        unsigned long int_part = (unsigned long) (q);
        // float
        unsigned long flt_part = (unsigned long) (((q - int_part) * s21_ten_power(precision) + .5));
        if (int_part % 2 == 1 && precision == 0) {
            int_part = (unsigned long) (q + 0.5);
        }
        /* build output float string */

        // write integer
        s21_sprintf(int_part_string + sign_space, "%lu", int_part);

        // write float
        char flt_part_format[32] = "";
        if (precision)
            s21_sprintf(flt_part_format, ".%%0%ldlu", precision);
        s21_sprintf(flt_part_string, flt_part_format, flt_part);
    }
    // build
    s21_size_t length =
        s21_strlen(int_part_string) + (precision ? s21_strlen(flt_part_string) : 0);
    s21_size_t shift =
        (format.width > (int) length)
        ? format.width - length : 0;

    if (format.left_align) {
        s21_sprintf(str, "%s%s", int_part_string, flt_part_string); str += length;
        s21_memset(str, format.blank, shift);
    } else {
        s21_memset(str, format.blank, shift); str += shift;
        s21_sprintf(str, "%s%s", int_part_string, flt_part_string);
    }

    // written
    return length + shift;
}
