#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "constants.h"
#include "structs.h"
#include "enums.h"

bool saved_word(char *);

bool is_directive(char *str);
bool is_operator(char *str);
bool isEffectLessLine(char *);
bool getLine(FILE *, char *);
bool validReg(char *);
void replace_multi_space_with_single_space(char *);

bool does_label_exist(char *, symbol_table);
bool validLabel(char *, symbol_table);
bool add_label(char *, int, label_type, symbol_table *);
void print_list(symbol_table);
int get_num_arguments(line);


void * malloc_safe(size_t size);
void * calloc_safe(size_t count, size_t size);
void * realloc_safe(void * ptr, size_t size);


#endif
