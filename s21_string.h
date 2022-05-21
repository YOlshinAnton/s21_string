#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#define S21_NULL ((void*)0)

typedef unsigned long s21_size_t;

/* memory manipulation */
void *s21_memchr(const void *str, int c, s21_size_t n);

int s21_memcmp(const void *str1, const void *str2, s21_size_t n);

void *s21_memcpy(void *dest, const void *src, s21_size_t n);

void *s21_memmove(void *dest, const void *src, s21_size_t n);

void *s21_memset(void *str, int c, s21_size_t n);

/* string manipulation */
char *s21_strcpy(char *dest, const char *src);

char *s21_strncpy(char *dest, const char *src, s21_size_t n);

char *s21_strcat(char *dest, const char *src);

char *s21_strncat(char *dest, const char *src, s21_size_t n);

/* string examination */
s21_size_t s21_strlen(const char *str);

int s21_strcmp(const char *str1, const char *str2);

int s21_strncmp(const char *str1, const char *str2, s21_size_t n);

char *s21_strchr(const char *str, int c);

char *s21_strrchr(const char *str, int c);

s21_size_t s21_strspn(const char *str1, const char *str2);

s21_size_t s21_strcspn(const char *str1, const char *str2);

char *s21_strpbrk(const char *str1, const char *str2);

char *s21_strstr(const char *haystack, const char *needle);

char *s21_strtok(char *restrict str, const char *restrict sep);

/* strerror */
extern char * const s21_sys_errlist[];;

char *s21_strerror(int errnum);

/* sprintf */
int s21_sprintf(char * restrict str, const char * restrict format, ...);

/* Special string processing functions */
void *s21_to_upper(const char *str);

void *s21_to_lower(const char *str);

void *s21_insert(const char *src, const char *str, s21_size_t start_index);

void *s21_trim(const char *src, const char *trim_chars);

#endif  // SRC_S21_STRING_H_
