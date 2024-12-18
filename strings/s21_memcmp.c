#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, my_size_t n) {
    unsigned char *s21_str1 = (unsigned char*)str1;
    unsigned char *s21_str2 = (unsigned char*)str2;
    int result = 0;

    for(my_size_t i = 0; i < n; i++) {
        if(s21_str1[i] != s21_str2[i]) {
            result = s21_str1[i] - s21_str2[i];
            break;
        }
    }
    return result;
}