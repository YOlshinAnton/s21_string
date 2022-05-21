#include "s21_string.h"

/* memory manipulation  */
void *s21_memchr(const void *str, int c, s21_size_t n) {
    void * cp = S21_NULL;

    const char * iterator = (const char*) str;
    while (n) {
        if (c == *iterator) {
            cp = (void*) iterator;
            break;
        }
        ++iterator; --n;
    }
    return cp;
}


void *s21_memcpy(void *dest, const void *src, s21_size_t len) {
    char *d = dest;
    const char *s = src;
    while (len--)
        *d++ = *s++;
    return dest;
}

int s21_memcmp(const void *s1, const void *s2, s21_size_t n) {
    int dif = 0;
    if (n != 0) {
        const unsigned char *p1 = s1, *p2 = s2;

        do {
            if (*p1++ != *p2++) {
                dif = (*--p1 - *--p2);
                break;
            }
        } while (--n != 0);
    }
    return dif;
}

void *s21_memmove(void *dest, const void *src, s21_size_t len) {
    char *d = dest;
    const char *s = src;
    if (d < s) {
        while (len--) *d++ = *s++;
    } else {
        char *lasts = (char*)s + (len-1);
        char *lastd = d + (len-1);
        while (len--)
            *lastd-- = *lasts--;
    }
    return dest;
}

void *s21_memset(void *dest, int val, s21_size_t len) {
    char *ptr = dest;
    while (len-- > 0)
        *ptr++ = val;
    return dest;
}

/*string manipulation */
char *s21_strcat(char *dest, const char *src) {
    char* ptr = dest;
    while (*ptr) ptr++;
    while (*src) *ptr++ = *src++;
    *ptr = 0;
    return dest;
}

char *s21_strncat(char* dist, const char* source, s21_size_t count) {
    char* str = dist;
    for (; *str; ++str) { ; }
    for (; *source && (count > 0); *str++ = *source++, --count) { ; }
    *str = 0;
    return dist;
}

/* string examination */
s21_size_t s21_strlen(const char *str) {
    s21_size_t len = 0;

    while (*str != 0) {
        len++; str++;
    }

    return len;
}

int s21_strcmp(const char *str1, const char *str2) {
    while (*str1) {
        if (*str1 != *str2) {
            break;
        }
        str1++;
        str2++;
    }
    return (unsigned char) *str1 - (unsigned char) *str2;
}

int s21_strncmp(const char* str1, const char* str2, s21_size_t num) {
    char* nulled = "";
    if (str1 == S21_NULL)
        str1 = nulled;
    if (str2 == S21_NULL)
        str2 = nulled;
    s21_size_t i = 0;
    for (; *str1 && *str2 && *str1 == *str2 && i < num; str1++, str2++, i++) {}
    return i < num ? *str1 - *str2 : 0;
}

char *s21_strchr(const char *str, int c) {
    char * pos = S21_NULL;
    while (*str != 0) {
        if (*str == c) {
            pos = (char*) str;
            break;
        }
        ++str;
    }
    return c == 0 ? (char*) str : pos;
}

char *s21_strrchr(const char *str, int c) {
    char * pos = S21_NULL;
    if (str != S21_NULL) {
        while (*str != 0) {
            if (*str == c) {
                pos = (char*) str;
            }
            ++str;
        }
    }
    return c == 0 ? (char*) str : pos;
}

char * s21_strcpy(char *s1, const char * s2) {
    char* dst = s1;
    while (*s2 != '\0') {
        *dst = *s2; dst++; s2++;
    }
    *dst = '\0';
    return s1;
}

char * s21_strncpy(char *s1, const char * s2, s21_size_t n) {
    char* dst = s1;

    while (*s2 && n > 0) {
        *dst++ = *s2++, --n;
    }
    *dst = '\0';
    return s1;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
    s21_size_t count = 0;

    while (*str1 != 0) {
        if (s21_strchr(str2, *str1) == S21_NULL) {
            break;
        }
        str1++; count++;
    }

    return count;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
    s21_size_t count = 0;

    while (*str1 != 0) {
        if (s21_strchr(str2, *str1) != S21_NULL) {
            break;
        }
        str1++; count++;
    }

    return count;
}

char *s21_strpbrk(const char *str1, const char *str2) {
    str1 += s21_strcspn(str1, str2);
    return *str1 ? (char *)str1 : S21_NULL;
}

static int compare(const char *s1, const char *s2) {
    while (*s1 & *s2) {
        if (*s1 != *s2) {
            break;
        }
        s1++; s2++;
    }
    return *s2 == '\0';
}

char * s21_strstr(const char *s1, const char *s2) {
    char * str = S21_NULL;
    if (s21_strlen(s2) != 0) {
        while (*s1 != '\0') {
            if ((*s1 == *s2) && compare(s1, s2)) {
                str = (char*) s1; break;
            }
            s1++;
        }
    } else {
        str = (char*) s1;
    }
    return str;
}

char *s21_strtok(char * str, const char * delim) {
    static char * old = S21_NULL;

    if (str) old = str;

    str = old;
    if (old && delim && *old) {
        old += s21_strcspn(old, delim);
        if (*old) {
            *old++ = 0;
            old += s21_strspn(old, delim);
        }
    } else {
        str = S21_NULL;
    }
    return str;
}
