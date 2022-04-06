#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 80


typedef enum boolean {
  FALSE = 0,
  TRUE = 1
} boolean;

typedef struct macros {
    char macro_name[MAX_LINE_LENGTH];
    char * macro_lines;
} macro;

void replace_multi_space_with_single_space(char *);
bool validReg(char *);
bool getLine(FILE *, char *);
bool isEffectLessLine(char *);
int end(FILE *src, FILE *dest, macro *macro_arr, int);
bool macro_func(FILE *, FILE *);




