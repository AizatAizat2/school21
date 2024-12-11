#ifndef MY_GREP
#define MY_GREP

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 100

typedef struct options {
  int e, i, v, c, l, n, s, h, f, o;
  char *pattern;
  int lenPattern;
  int multFiles;

} opt;

int my_getline(char **line, size_t *len, FILE *stream) {

  int result = 0;

  if (line == NULL || len == NULL || stream == NULL) {
    result = -1;
  }

  size_t size = *len;
  size_t i = 0;
  int c = 0;

  if (*line == NULL) {
    *line = (char *)malloc(INITIAL_SIZE);
    if (*line == NULL) {
      result = -1;
    }
    size = INITIAL_SIZE;
  }

  while ((c = fgetc(stream)) != EOF) {
    if (c == '\n') {
      break;
    }

    if (i >= size - 1) {
      size_t new_size = size * 2;
      char *new_line = (char *)realloc(*line, new_size);
      if (new_line == NULL) {
        result = -1;
      }
      *line = new_line;
      size = new_size;
    }

    (*line)[i++] = (char)c;
  }

  if (i == 0 && c == EOF) {
    result = -1;
  }

  (*line)[i] = '\0';

  *len = size;
  if(result != -1) {
  result = i;
  }
  return result;
}

#endif
