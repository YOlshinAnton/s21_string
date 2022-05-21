#include "s21_string.h"
#include <stdlib.h>

/* Special string processing functions */
void *s21_to_upper(const char *str) {
    char *result = S21_NULL;
    result = (char*)malloc(sizeof(char) * s21_strlen(str)+1);
    s21_strcpy(result, str);
    s21_size_t i = 0;
    while (i < s21_strlen(result)) {
        if ((result[i] >= 'a' && result[i]<= 'z')) {
            result[i] -= 32;
        }
        i++;
    }
    return result;
}

void *s21_to_lower(const char *str) {
    char *result = S21_NULL;
    result = (char*)malloc(sizeof(char) * s21_strlen(str)+1);
    s21_strcpy(result, str);

    s21_size_t i = 0;
    while (i < s21_strlen(result)) {
        if (result[i] >= 'A' && result[i]<= 'Z') {
            result[i] += 32;
        }
        i++;
    }
    return result;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    char *result = S21_NULL;
    s21_size_t src_len = 0; src_len += s21_strlen(src);
    s21_size_t str_len = 0; str_len += s21_strlen(str);
    if (start_index <= src_len) {
        result = (char *) malloc(sizeof(char) * (src_len + str_len + 1));
        *result = 0;
        s21_strncpy(result, src, start_index);
        s21_strcat(result, str);
        s21_strcat(result, src + start_index);
    }
    return result;
}

void *s21_trim(const char *src, const char *trim_chars) {
    char *result = S21_NULL;
    const s21_size_t trim_before = s21_strspn(src, trim_chars);
    s21_size_t non_trimed = 0;
    s21_size_t non_trimed_step = 0;
    s21_size_t trimed_step = 0;
    const char * sp = src + trim_before;
    while (*(sp)) {
        non_trimed_step = s21_strcspn(sp, trim_chars);
        trimed_step = s21_strspn(sp, trim_chars);
        sp += non_trimed_step + trimed_step;
        if (*sp) {
            non_trimed += non_trimed_step + trimed_step;
        } else {
            non_trimed += non_trimed_step;
        }
    }
    result = (char*) malloc(non_trimed + 1);
    s21_strncpy(result, src + trim_before, non_trimed);
    *(result + non_trimed) = 0;
    return result;
}
