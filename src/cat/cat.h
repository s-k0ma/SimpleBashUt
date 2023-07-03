#ifndef CAT
#define CAT
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../common/system.h"

struct catoptions {
  int b;
  int n;
  int s;
  int e;
  int E;
  int t;
  int T;
  int v;
  int flag;
};

struct catoptions initcat(int argc, char** argv);
void runcat(int argc, char** argv, struct catoptions opt);
void nFlag(FILE* out, int flag);
void sFlag(FILE* out);
void vFlag(FILE* out, int flag);
char* submission(int index);

#endif
