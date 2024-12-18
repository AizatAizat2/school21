#include "s21_string.h"

int s21_sprintf(char *str, const char* format, ...) {
    my_size_t size = my_strlen(format);

    for(my_size_t i = 0; i < size; i++) {
        if(format[i] == '%') {
            switch(format[i++]) {
                case 'd':
                
            }
        }
    }
}