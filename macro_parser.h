#ifndef MACRO_PARSER_H
#define MACRO_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "enums.h"
#include "utils.h"

void replace_multi_space_with_single_space(char *);
bool validReg(char *);
bool getLine(FILE *, char *);
bool isEffectLessLine(char *);
void end(macro_list * macros);
bool does_macro_exist(char *name, struct macro_list p1, FILE *dest);
macro * add_macro(char *name, struct macro_list *p1);
void add_macro_line(char *line, macro *node);
void print_macro_list(struct macro_list p1);
bool macro_func(FILE *, FILE *);

#endif
