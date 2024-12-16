#include "s21_string.h"

my_size_t s21_strlen(const char *str) { 
    my_size_t n = 0;
    while(str[n] != '\0') {
        n++;
    }
    return n;
}