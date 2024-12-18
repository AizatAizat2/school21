CC = gcc
СFLAGS = -Wall -Werror -Wextra -std=c11

TARGET = s21_test

SRC_DIR = .

INCLUDES = -I$(SRC_DIR)

MAIN_SRC = $(SRC_DIR)/s21_test.c

SRC = $(wildcard $(SRC_DIR)/s21_*.c)

OBJ = $(SRC:.c=.o)
MAIN_OBJ = $(MAIN_SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ) $(MAIN_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(INCLUDES) -lcheck -lrt -lm -lpthread -lsubunit

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/s21_string.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ) $(MAIN_OBJ) $(TARGET)

rebuild: clean all