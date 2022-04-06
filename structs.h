#include "enums.h"

#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct word {
  int data;
  ARE end;
} word;

typedef struct line {

} line;


typedef struct data_node {
  char * data;
  int address; // or int lineNum;
  data_node * next;
} data_node;

// linked list of all the data instructions
typedef struct data_image {
 data_node * head;
 data_node * tail;
 int size;
} data_image;

typedef struct code_node {
  char * code;
  int address; // or int lineNum;
  code_node * next;
} code_node;

// linked list of all the code
typedef struct code_image {
 code_node * head;
 code_node * tail;
 int size;
} code_image;

typedef struct symbol_node {
	char * symbolName;
  int address; // or int lineNum;
	symbol_node * next;
} symbol_node;

// linked list of all the symbols
typedef struct symbol_table {
	symbol_node * head;
	symbol_node * tail;
  int size;
};


#endif