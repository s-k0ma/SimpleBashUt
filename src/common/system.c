#include "system.h"

FILE* openfile(char* filename) {
  FILE* fp = NULL;
  if ((fp = fopen(filename, "rb")) == NULL)
    return NULL;
  else
    return fp;
}

void scanner(FILE* temp, char* filename) {
  FILE* fp = NULL;
  int ch = 0;
  if ((fp = openfile(filename)) != NULL) {
    while ((ch = fgetc(fp)) != EOF) {
      fprintf(temp, "%c", ch);
    }
  } else
    fprintf(stderr, "No such file or directory\n");
  fclose(fp);
}

void printfile(FILE* out) {
  rewind(out);
  int ch = 0;
  if (out != NULL) {
    while ((ch = fgetc(out)) != EOF) {
      printf("%c", ch);
    }
  } else
    fprintf(stderr, "No such file or directory\n");
}

void copyfile(FILE* out, FILE* temp) {
  rewind(temp);
  int ch = 0;

  if (temp != NULL)
    while ((ch = getc(temp)) != EOF) {
      fprintf(out, "%c", ch);
    }
  else
    fprintf(stderr, "No such file or directory\n");
}

void increase(char*** input, size_t* size, char* line) {
  (*size)++;
  char** temp = (char**)realloc(*input, sizeof(char*) * (*size));
  if (temp == NULL) {
    fprintf(stderr, "Increasing failed.\n");
    return;
  }
  *input = temp;

  (*input)[(*size) - 1] = (char*)malloc(sizeof(char) * (strlen(line) + 1));
  if ((*input)[(*size) - 1] == NULL) {
    fprintf(stderr, "Increasing failed.\n");
    return;
  }
  memcpy((*input)[(*size) - 1], line, strlen(line) + 1);
}

void rmline(char*** input, size_t* size, char* rem) {
  if ((*input) != NULL) {
    int index = 0;
    for (int i = 0; i < (int)(*size); i++) {
      if (strcmp((*input)[i], rem) == 0) {
        index = i;
        break;
      }
    }
    for (int i = index; i < (int)(*size) - 1; i++) {
      char* temp = (*input)[i];
      (*input)[i] = (*input)[i + 1];
      (*input)[i + 1] = temp;
    }

    free((*input)[(int)(*size - 1)]);
    (*size)--;
    *input = (char**)realloc(*input, sizeof(char*) * (*size));
  }
}

void renlch(char* str) {
  size_t nlpos = strcspn(str, "\n");
  if (str[nlpos] == '\n') str[nlpos] = '\0';
}

char* readline(FILE* fp) {
  char* line = NULL;
  size_t len = 0;
  size_t cap = 0;
  int ch = 0;

  while ((ch = fgetc(fp)) != EOF) {
    if (len + 1 >= cap) {
      cap += 64;
      char* temp = realloc(line, cap);
      if (temp == NULL) {
        fprintf(stderr, "Allocate memory failed\n");
        free(line);
        return NULL;
      }
      line = temp;
    }
    line[len++] = ch;
    if (ch == '\n') break;
  }

  if (len > 0) line[len] = '\0';
  return line;
}
