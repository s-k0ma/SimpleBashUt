#ifndef GREP
#define GREP
#include <getopt.h>
#include <regex.h>

#include "../common/system.h"

struct grepoptions {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int flag;
  char** patterns;
  char** files;
  size_t fCounter;
  size_t pCounter;
};

struct grepoptions initgrep(int argc, char** argv);
void rungrep(struct grepoptions opt);
int simplegrep(struct grepoptions* ptr, char* filename);
int match(char* pat, char* line, char** token, struct grepoptions* opt,
          char** out);
void printbyopts(int counter, struct grepoptions* ptr, char* filename);
void ocat(char** out, char* token, size_t size);

#endif
