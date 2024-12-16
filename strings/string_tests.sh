#!/bin/bash

gcc s21_string.h test.c s21_strlen.c -lcheck -lm -lpthread -o s21_string_test
chmod +x s21_string_test
./s21_string_test
rm -rf s21_string_test