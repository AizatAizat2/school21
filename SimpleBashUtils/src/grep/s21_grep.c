#include "s21_grep.h"

int length(char *str) {
  int len = 0;
  while (str[len] != '\0') {
    len++;
  }
  return len;
}

void addChar(char **str, int *len, char c) {
  (*len)++;
  char *temp = realloc(*str, (*len) * sizeof(char));

  if (temp == NULL) {
    perror("Realloc failed");
  } else {
    *str = temp;
    (*str)[*len - 1] = c;
  }
}

void addPattern(opt *options, char *newPattern) {
  int len = length(newPattern);
  if (options->lenPattern != 0) {
    addChar(&options->pattern, &options->lenPattern, '|');
  }
  addChar(&options->pattern, &options->lenPattern, '(');
  for (int i = 0; i < len; i++) {
    addChar(&options->pattern, &options->lenPattern, newPattern[i]);
  }
  addChar(&options->pattern, &options->lenPattern, ')');
}

void addPatternFile(opt *options, char *newPattern) {
  FILE *pattern_file = fopen(newPattern, "r");
  char *line = NULL;
  size_t length;
  int read = 0;

  if (pattern_file == NULL) {
    perror("Error");
  } else {
    while ((read = my_getline(&line, &length, pattern_file)) != -1) {
      addPattern(options, line);
    }
    if (line != NULL) {
      free(line);
    }

    fclose(pattern_file);
  }
}

void parser(int argc, char *argv[], opt *options) {
  int opt = 0;
  while ((opt = getopt(argc, argv, "e:ivclnshf:o")) != -1) {
    switch (opt) {
      case 'e':
        options->e = 1;
        addPattern(options, optarg);
        break;
      case 'i':
        options->i = REG_ICASE;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'c':
        options->c = 1;
        break;
      case 'l':
        options->l = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 'h':
        options->h = 1;
        break;
      case 'o':
        options->o = 1;
        break;
      case 'f':
        options->f = 1;
        addPatternFile(options, optarg);
        break;
    }
  }
  if (options->pattern == NULL) {
    addPattern(options, argv[optind]);
    optind++;
  }
}

void print_match(regex_t *re, char *line, opt *options, char **filename,
                 int count) {
  regmatch_t math;
  int offset = 0;
  while (1) {
    int result = regexec(re, line + offset, 1, &math, 0);

    if (result != 0) {
      break;
    }

    if (options->multFiles == 1) {
      printf("%s:", filename[count]);
    }

    for (int i = math.rm_so; i < math.rm_eo; i++) {
      putchar((line + offset)[i]);
    }

    putchar('\n');

    offset += math.rm_so + 1;
  }
}

void base_func(char **filename, int count, FILE *file, regex_t re,
               opt *options) {
  char *line = NULL;
  size_t length;
  int read = 0;

  int line_count = 1;
  int matching_count = 0;

  while ((read = my_getline(&line, &length, file)) != -1) {
    int result = regexec(&re, line, 0, NULL, 0);

    if (result == options->v) {
      if (options->c != 1 && options->l != 1 && options->h != 1 &&
          options->o != 1) {
        if (options->multFiles == 1) {
          printf("%s:", filename[count]);
        }
        if (options->n == 1) printf("%d:", line_count);

        printf("%s\n", line);

      } else if (options->c == 1 || options->l == 1) {
        matching_count++;
      }

      if (options->f == 1) {
        printf("%d", options->f);
      }

      if (options->h == 1) {
        printf("%s\n", line);
      }

      if (options->o == 1) {
        print_match(&re, line, options, filename, count);
      }
    }

    line_count++;
  }

  if (options->c == 1 && options->l != 1) {
    if (options->multFiles == 1) printf("%s:", filename[count]);
    printf("%d\n", matching_count);
  }
  if (options->l == 1 && matching_count > 0) printf("%s\n", filename[count]);
  free(line);
  regfree(&re);
  fclose(file);
}

void outline(char **filename, opt *options, int count) {
  regex_t re;
  int error = regcomp(&re, options->pattern, REG_EXTENDED | options->i);

  if (error == 1) {
    perror("Error");
  } else {
    FILE *file = fopen(filename[count], "r");

    if (file == NULL) {
      if (options->s != 1) {
        perror("Error");
      }
      regfree(&re);
    } else {
      base_func(filename, count, file, re, options);
    }
  }
}

int main(int argc, char *argv[]) {
  opt options = {0};
  parser(argc, argv, &options);
  addChar(&options.pattern, &options.lenPattern, '\0');
  options.multFiles = (argc - optind > 1) ? 1 : 0;
  for (int i = optind; i < argc; i++) {
    outline(argv, &options, i);
  }
  if (options.pattern != NULL) {
    free(options.pattern);
    options.pattern = NULL;
  }
  return 0;
}
