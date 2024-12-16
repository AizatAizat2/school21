CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
LFGLAGS = -lcheck -lm -lpthread -l s21_string.a
SOURCE = $(wildcard s21_*.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCE))

all:
	clean
	test.o
	s21_string.a
	test

test: test.o s21_string.a
	$(CC) $(FLAGS) $(LFLAGS) -o test test.o
	chmod +x test
	./test

test.o: test.c s21_string.h
	$(CC) $(FLAGS) -c test.c -o test.o

s21_string.a: $(OBJECTS)
	ar rcs s21_string.a $(OBJECTS)

$(OBJECTS):
	$(CC) $(FLAGS) -c s21_string.h $(SOURCE)

clean:
	rm -rf s21_string.a s21_string_test *.o *.gcda *.gcno *.gcov *.gch