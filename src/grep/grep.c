#include "grep.h"

int main(int argc, char** argv) {
  rungrep(initgrep(argc, argv));

  return 0;
}

int simplegrep(struct grepoptions* ptr, char* filename) {
  int counter = 0;
  FILE* fp = openfile(filename);
  int numlines = 0;
  if (fp == NULL) {
    if (ptr->s == 0) fprintf(stderr, "No such file or directory\n");
    return 0;
  }
  char* line = NULL;
  while ((line = readline(fp)) != NULL) {
    renlch(line);
    numlines++;
    char* token = line;
    char* out = NULL;
    int matched = 0;
    for (int i = 0; i < (int)ptr->pCounter; i++) {
      if (!match(ptr->patterns[i], token, &token, ptr, &out)) {
        matched++;
        if (ptr->o == 'o') {
          int c = (i + 1 == (int)ptr->pCounter ? i : (i + 1));
          while (!match(ptr->patterns[c], token, &token, ptr, &out))
            ;
        }
      }
    }
    if ((ptr->v == 0 && matched != 0) ||
        (ptr->v != 0 && matched == (int)ptr->pCounter)) {
      if (ptr->l == 0 && ptr->c == 0) {
        if (ptr->fCounter > 1 && ptr->h == 0) printf("%s:", filename);
        if (ptr->n != 0) printf("%d:%s\n", numlines, out);
        if (ptr->n == 0) printf("%s\n", out);
      }
      counter++;
    }
    if (ptr->o == 'o') free(out);
    free(line);
  }
  if (ptr->c != 0) {
    if (ptr->fCounter > 1 && ptr->h == 0) printf("%s:", filename);
    printf("%d\n", (ptr->l == 0 ? counter : (counter >= 1 ? 1 : 0)));
  }
  if (ptr->l != 0 && counter != 0) printf("%s\n", filename);
  fclose(fp);
  return counter;
}

void rungrep(struct grepoptions opt) {
  struct grepoptions* ptr = &opt;
  if (opt.flag == 0 && opt.fCounter != 0) {
    for (int i = 0; i < (int)opt.fCounter; i++) {
      simplegrep(ptr, opt.files[i]);
    }
  } else {
    if (opt.flag != 0) fprintf(stderr, "Illegal command %c\n", opt.flag);
  }
  for (int i = 0; i < (int)opt.pCounter; i++) free(opt.patterns[i]);
  for (int i = 0; i < (int)opt.fCounter; i++) free(opt.files[i]);
  free(opt.files);
  free(opt.patterns);
}

struct grepoptions initgrep(int argc, char** argv) {
  struct grepoptions opt;
  opt.e = 0;
  opt.i = 0;
  opt.v = 0;
  opt.c = 0;
  opt.l = 0;
  opt.n = 0;
  opt.h = 0;
  opt.s = 0;
  opt.f = 0;
  opt.o = 0;
  opt.flag = 0;
  opt.pCounter = 0;
  opt.fCounter = 0;
  opt.files = NULL;
  opt.patterns = NULL;
  int option = 0;

  if (argc > 1) {
    do {
      if ((option = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
        switch (option) {
          case 'e':
            opt.e = 'e';
            increase(&opt.patterns, &opt.pCounter, optarg);
            break;
          case 'i':
            opt.i = 'i';
            break;
          case 'v':
            opt.v = 'v';
            break;
          case 'c':
            opt.c = 'c';
            break;
          case 'l':
            opt.l = 'l';
            break;
          case 'n':
            opt.n = 'n';
            break;
          case 'h':
            opt.h = 'h';
            break;
          case 's':
            opt.s = 's';
            break;
          case 'f':
            opt.f = 'f';
            FILE* fp = openfile(optarg);
            if (fp == NULL) {
              fprintf(stderr, "No such file or directory\n");
              break;
            } else {
              char* line = NULL;
              while ((line = readline(fp)) != NULL) {
                renlch(line);
                increase(&opt.patterns, &opt.pCounter, line);
                free(line);
              }
            }
            fclose(fp);
            break;
          case 'o':
            opt.o = 'o';
            break;
        }
      } else {
        increase(&opt.files, &opt.fCounter, argv[optind]);
        optind++;
      }
    } while (optind < argc);
  }
  if (opt.e == 0 && opt.f == 0) {
    for (int i = 1; i < argc; i++) {
      if (argv[i][0] != '-') {
        increase(&opt.patterns, &opt.pCounter, argv[i]);
        rmline(&opt.files, &opt.fCounter, argv[i]);
        break;
      }
    }
  }
  return opt;
}

int match(char* pat, char* line, char** token, struct grepoptions* ptr,
          char** out) {
  regex_t rx;
  regmatch_t match;
  size_t shift = 1;
  int res = 1;
  int reg = 0;

  regcomp(&rx, pat, (ptr->i == 'i' ? REG_ICASE : REG_EXTENDED));
  reg = regexec(&rx, line, 1, &match, 0);
  if ((ptr->v == 0 && reg == 0) || (ptr->v == 'v' && reg != 0)) {
    if (ptr->o == 'o') {
      if (ptr->v == 0) {
        size_t size = match.rm_eo - match.rm_so;
        shift += match.rm_so;
        if (shift >= strlen(line)) {
          regfree(&rx);
          return 1;
        }
        *token += shift;
        ocat(out, (line + match.rm_so), size);
        res = 0;
      } else {
        res = 1;
      }
    } else {
      res = 0;
      *out = line;
    }
  }
  regfree(&rx);
  return res;
}

void ocat(char** out, char* token, size_t size) {
  if (*out == NULL) {
    *out = strndup(token, size);
  } else {
    size_t cur = strlen(*out);
    char* buf = realloc(*out, sizeof(char) * (size + cur + 2));
    if (buf != NULL) {
      buf[cur] = '\n';  // Add newline character
      strncpy(buf + cur + 1, token, size);
      buf[cur + size + 1] = '\0';  // Ensure null termination
      *out = buf;
    } else {
      free(*out);
      *out = NULL;
    }
  }
}
