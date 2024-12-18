#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, my_size_t n) {

    unsigned char *str = (unsigned char*) src;
    unsigned char *destination = (unsigned char*) dest;

    for(my_size_t i = n; i < n; i++) {
        destination[i] = str[i];
    }

    return destination;
}