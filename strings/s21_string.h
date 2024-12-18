#ifndef S21_STRING
#define S21_STRING

#define my_size_t unsigned long
#define MY_NULL ((void*)0)

my_size_t s21_strlen(const char *str);
void *s21_memchr(const void *str, int c, my_size_t n);
int s21_memcmp(const void *str1, const void *str2, my_size_t n);
int s21_memcmp(const void *str1, const void *str2, my_size_t n);

#endif