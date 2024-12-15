#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct options {
  int b, e, v, n, s, t;
  int multFiles;
} opt;

void parser(int argc, char *argv[], opt *options) {
  int opt = 0;
  struct option long_option[] = {{"number", no_argument, NULL, 'n'},
                                 {"squeeze-blank", no_argument, NULL, 's'},
                                 {"number-nonblank", no_argument, NULL, 'b'},
                                 {0, 0, 0, 0}};

  while ((opt = getopt_long(argc, argv, "+bevnstTE", long_option, NULL)) !=
         -1) {
    switch (opt) {
      case 'b':
        options->b = 1;
        break;

      case 'e':
        options->e = 1;
        options->v = 1;
        break;

      case 'v':
        options->v = 1;
        break;

      case 'n':
        options->n = 1;
        break;

      case 's':
        options->s = 1;
        break;

      case 't':
        options->t = 1;
        options->v = 1;
        break;

      case 'T':
        options->t = 1;
        break;

      case 'E':
        options->e = 1;
        break;

      default:
        exit(1);
    }
  }
}

void numstr_n(int *strCount, int *flag_bn, int ch) {
  
  if (*flag_bn == 1) {
    printf("%6d\t", ++(*strCount));
    *flag_bn = 0;
  }
  if (ch == '\n') {
    *flag_bn = 1;
  }

}


void numstr_b(int *strCount, int *flag_bn, int ch) {
  
  
  if (*flag_bn == 1 && ch != '\n') {
    printf("%6d\t", ++(*strCount));
    *flag_bn = 0;
  }

  if (ch == '\n') {
    *flag_bn = 1;
  }

}

void numstr_s(int *strCount, int *ch, int *prev_newline) {

 if (*ch == '\n') {
    if (*prev_newline == 0) {
      putchar(*ch);
      *prev_newline = 1;
      *strCount = 0;
    } else {
      (*strCount)++;
    }
  } else {
    if (*strCount > 0) {
      putchar('\n');
      *strCount = 0;
    }
    putchar(*ch);
    *prev_newline = 0;
  }

}



void numstr_t(int *ch) {
  if (*ch == 9) {
    putchar('^');
    *ch = 'I';
  }
}

void numstr_v(int *ch) {
  if (*ch != 9 && *ch < 32 && *ch != 10) {
    *ch += 64;
    putchar('^');
  }
  if (*ch == 127) {
    putchar('^');
    *ch -= 64;
  }
  if (*ch > 127) {
    putchar('M');
    putchar('-');
    *ch -= 128;
  }
}

void outline(char **file, opt options, int optind, int *strCount, int *flag_bn) {
  int flag_error = 0;
  int ch = 0;
  int prev_newline = 1;

  FILE *name = fopen(file[optind], "r");
  if (name == NULL) {
    perror("./s21_cat");
  } else {
    while ((ch = getc(name)) != EOF) {

      if (options.e == 1 && ch == '\n') 
      putchar('$');  // вывод $
      if (options.n == 1 && !options.b)
        numstr_n(strCount, flag_bn, ch);  // вывод номера всех строк
      if (options.b == 1 && !options.n)
        numstr_b(strCount, flag_bn, ch);  // вывод номера непустых строк
      if (options.s == 1 && flag_error != 1)
         numstr_s(strCount, &ch, &prev_newline);
      if (options.t == 1) numstr_t(&ch);
      if (options.v == 1) numstr_v(&ch);

      if (ch != EOF && options.s != 1) {
        putchar(ch);
      }

    }

  fclose(name);
}
}

int main(int argc, char *argv[]) {
  opt options = {0};
  parser(argc, argv, &options);
  int strCount = 0;
  int flag_bn = 1;
  for (int i = optind; i < argc; i++) {
    outline(argv, options, i, &strCount, &flag_bn);
  }

  return 0;
}