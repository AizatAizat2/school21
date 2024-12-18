#include "s21_string.h"

void *s21_memchr(const void *str, int c, my_size_t n) {
    unsigned char *s = (unsigned char*) str;
    unsigned char ch = (unsigned char) c;
    void *find_bite = MY_NULL;

    for(int i = 0; i < n; i++) {
        if(s[i] == c) {
            find_bite = s + i; 
            break;
        }
    }
    return find_bite;
}