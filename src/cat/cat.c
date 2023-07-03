#include "cat.h"

int main(int argc, char** argv) {
  runcat(argc, argv, initcat(argc, argv));

  return 0;
}

void vFlag(FILE* out, int flag) {
  FILE* temp = tmpfile();
  int index = 0;
  rewind(out);

  if (out != NULL) {
    while ((index = fgetc(out)) != EOF) {
      switch (flag) {
        case 'e':
          if (index < 256 && index != 9) {
            fprintf(temp, "%s", submission(index));
          } else
            fputc(index, temp);
          break;
        case 'E':
          if (index == 10)
            fprintf(temp, "%s", submission(index));
          else
            fputc(index, temp);
          break;
        case 't':
          if (index < 256 && index != 10)
            fprintf(temp, "%s", submission(index));
          else
            fputc(index, temp);
          break;
        case 'T':
          if (index == 9)
            fprintf(temp, "%s", submission(index));
          else
            fputc(index, temp);
          break;
        case 'v':
          if (index < 256 && index != 10 && index != 9)
            fprintf(temp, "%s", submission(index));
          else
            fputc(index, temp);
      }
    }
  }
  rewind(out);
  copyfile(out, temp);
  fclose(temp);
}

void nFlag(FILE* out, int flag) {
  FILE* temp = tmpfile();
  int counter = 0;
  int mark = 1;
  int ch = 0;
  int pre = '\n';
  rewind(out);
  if (out != NULL) {
    while ((ch = fgetc(out)) != EOF) {
      switch (flag) {
        case 'n':
          if (mark == 1) {
            fprintf(temp, "%6d\t", ++counter);
            mark = 0;
          }
          fprintf(temp, "%c", ch);
          if (ch == '\n') mark = 1;
          break;
        case 'b':
          if (ch != '\n' && pre == '\n') mark = 0;
          if (mark == 0) {
            fprintf(temp, "%6d\t", ++counter);
            mark = 1;
          }
          fprintf(temp, "%c", ch);
          pre = ch;
          break;
        case 's':
          if (ch != '\n') {
            fprintf(temp, "%c", ch);
            counter = 0;
          } else {
            if (pre == '\n') counter++;
            if (counter <= 1) fprintf(temp, "%c", ch);
          }
          pre = ch;
          break;
      }
    }
  } else
    fprintf(stderr, "No such file or directory\n");

  fseek(out, 0, SEEK_SET);
  copyfile(out, temp);
  int trim = 0;
  if ((trim = ftruncate(fileno(out), (off_t)ftell(temp))) == -1)
    fprintf(stderr, "Trim file problem");

  fclose(temp);
}

char* submission(int index) {
  char* replacement_HT[] = {
      "^@",   "^A",   "^B",   "^C",    "^D",   "^E",   "^F",   "^G",   "^H",
      "^I",   "$\n",  "^K",   "^L",    "^M",   "^N",   "^O",   "^P",   "^Q",
      "^R",   "^S",   "^T",   "^U",    "^V",   "^W",   "^X",   "^Y",   "^Z",
      "^[",   "^\\",  "^]",   "^^",    "^_",   " ",    "!",    "\"",   "#",
      "$",    "%",    "&",    "\'",    "(",    ")",    "*",    "+",    ",",
      "-",    ".",    "/",    "0",     "1",    "2",    "3",    "4",    "5",
      "6",    "7",    "8",    "9",     ":",    ";",    "<",    "=",    ">",
      "?",    "@",    "A",    "B",     "C",    "D",    "E",    "F",    "G",
      "H",    "I",    "J",    "K",     "L",    "M",    "N",    "O",    "P",
      "Q",    "R",    "S",    "T",     "U",    "V",    "W",    "X",    "Y",
      "Z",    "[",    "\\",   "]",     "^",    "_",    "`",    "a",    "b",
      "c",    "d",    "e",    "f",     "g",    "h",    "i",    "j",    "k",
      "l",    "m",    "n",    "o",     "p",    "q",    "r",    "s",    "t",
      "u",    "v",    "w",    "x",     "y",    "z",    "{",    "|",    "}",
      "~",    "^?",   "M-^@", "M-^A",  "M-^B", "M-^C", "M-^D", "M-^E", "M-^F",
      "M-^G", "M-^H", "M-^I", "M-^J",  "M-^K", "M-^L", "M-^M", "M-^N", "M-^O",
      "M-^P", "M-^Q", "M-^R", "M-^S",  "M-^T", "M-^U", "M-^V", "M-^W", "M-^X",
      "M-^Y", "M-^Z", "M-^[", "M-^\\", "M-^]", "M-^^", "M-^_", "M- ",  "M-!",
      "M-\"", "M-#",  "M-$",  "M-%",   "M-&",  "M-'",  "M-(",  "M-)",  "M-*",
      "M-+",  "M-,",  "M--",  "M-.",   "M-/",  "M-0",  "M-1",  "M-2",  "M-3",
      "M-4",  "M-5",  "M-6",  "M-7",   "M-8",  "M-9",  "M-:",  "M-;",  "M-<",
      "M-=",  "M->",  "M-?",  "M-@",   "M-A",  "M-B",  "M-C",  "M-D",  "M-E",
      "M-F",  "M-G",  "M-H",  "M-I",   "M-J",  "M-K",  "M-L",  "M-M",  "M-N",
      "M-O",  "M-P",  "M-Q",  "M-R",   "M-S",  "M-T",  "M-U",  "M-V",  "M-W",
      "M-X",  "M-Y",  "M-Z",  "M-[",   "M-\\", "M-]",  "M-^",  "M-_",  "M-`",
      "M-a",  "M-b",  "M-c",  "M-d",   "M-e",  "M-f",  "M-g",  "M-h",  "M-i",
      "M-j",  "M-k",  "M-l",  "M-m",   "M-n",  "M-o",  "M-p",  "M-q",  "M-r",
      "M-s",  "M-t",  "M-u",  "M-v",   "M-w",  "M-x",  "M-y",  "M-z",  "M-{",
      "M-|",  "M-}",  "M-~",  "M-^?"};

  return replacement_HT[index];
}

struct catoptions initcat(int argc, char** argv) {
  struct catoptions opt;
  opt.b = 0;
  opt.n = 0;
  opt.s = 0;
  opt.e = 0;
  opt.E = 0;
  opt.t = 0;
  opt.T = 0;
  opt.v = 0;
  opt.flag = 0;
  struct option longopts[] = {{"number-nonblank", no_argument, NULL, 'b'},
                              {"number", no_argument, NULL, 'n'},
                              {"squeeze-blank", no_argument, NULL, 's'},
                              {NULL, 0, NULL, 0}};
  int option = 0;
  do {
    if ((option = getopt_long(argc, argv, "bnseEtTv", longopts, NULL)) != -1) {
      switch (option) {
        case 'b':
          opt.b = 'b';
          break;
        case 'n':
          opt.n = 'n';
          break;
        case 's':
          opt.s = 's';
          break;
        case 'e':
          opt.e = 'e';
          break;
        case 'E':
          opt.E = 'E';
          break;
        case 't':
          opt.t = 't';
          break;
        case 'T':
          opt.T = 'T';
          break;
        case 'v':
          opt.v = 'v';
          break;
        case '?':
          opt.flag = 1;
          break;
      }
    } else
      optind++;
  } while (optind < argc);
  return opt;
}

void runcat(int argc, char** argv, struct catoptions opt) {
  if (opt.flag == 0) {
    FILE* output = tmpfile();
    if (opt.b == 'b') opt.n = 0;
    if (opt.t == 't') opt.T = 0;
    if (opt.e == 'e') opt.E = 0;
    for (int i = 1; i < argc; i++) {
      if (argv[i][0] != '-') {
        FILE* buff = tmpfile();
        scanner(buff, argv[i]);
        if (opt.s == 's') nFlag(buff, opt.s);
        if (opt.t == 't') vFlag(buff, opt.t);
        if (opt.T == 'T') vFlag(buff, opt.T);
        if (opt.b == 'b') nFlag(buff, opt.b);
        if (opt.e == 'e') vFlag(buff, opt.e);
        if (opt.E == 'E') vFlag(buff, opt.E);
        if (opt.v == 'v') vFlag(buff, opt.v);
        if (opt.n == 'n') nFlag(buff, opt.n);
        copyfile(output, buff);
        fclose(buff);
      }
    }
    printfile(output);
    fclose(output);
  }
}
