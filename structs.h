#ifndef STRUCTS_H
#define STRUCTS_H

#include "enums.h"
#include "constants.h"

typedef struct word {
  char * data;
  ARE end;
} word;

typedef struct line {
  char text[MAX_LINE_LENGTH];
  int length;
  line_type type;
  int line_num;
  char ** parsed_line;
} line;

typedef struct data_node {
  word data;
  int address; // or int lineNum;
  struct data_node * next;
} data_node;

// linked list of all the data instructions
typedef struct data_image {
 data_node * head;
 int size;
} data_image;

typedef struct code_node {
  word code;
  int address; // or int lineNum;
  struct code_node * next;
} code_node;

// linked list of all the code
typedef struct code_image {
 code_node * head;
 int size;
} code_image;

typedef struct symbol_node {
	char * symbolName;
  label_type type;
  int address; // or int lineNum;
	struct symbol_node * next;
} symbol_node;

// linked list of all the symbols
typedef struct symbol_table {  
	symbol_node * head;
  int size;  
} symbol_table;

typedef struct macro_line {
    char line[MAX_LINE_LENGTH];
    struct macro_line *next;
} macro_line;

typedef struct macro {
    char macro_name[MAX_LINE_LENGTH];
    macro_line *head;
    macro_line *tail;
    struct macro *next;
} macro;

typedef struct macro_list{
    macro *head;
} macro_list;

#endif
