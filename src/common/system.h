#ifndef SYS
#define SYS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* openfile(char* filename);
void scanner(FILE* temp, char* filename);
void printfile(FILE* out);
void copyfile(FILE* out, FILE* temp);
void increase(char*** input, size_t* size, char* line);
void rmline(char*** input, size_t* size, char* rem);
void renlch(char* str);
char* readline(FILE* fp);

#endif
