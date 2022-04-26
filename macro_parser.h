#ifndef MACRO_PARSER_H
#define MACRO_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "enums.h"
#include "util.h"

void replace_multi_space_with_single_space(char *);
bool validReg(char *);
bool getLine(FILE *, char *);
bool isEffectLessLine(char *);
int end(FILE *src, FILE *dest, macro *macro_arr, int);
bool macro_func(FILE *, FILE *);

#endif
