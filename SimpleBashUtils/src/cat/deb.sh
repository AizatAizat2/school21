#!/bin/bash

FLAGS="-s"
FILE="../examples/*"

make clean
make s21_cat

cat $FLAGS $FILE > test1.txt
./s21_cat $FLAGS $FILE > test2.txt
diff test1.txt test2.txt

#rm -rf test1.txt test2.txt