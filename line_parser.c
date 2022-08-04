#include "line_parser.h"

void parse_line(line * current_line) {
  char ** parsed_line = malloc_safe(LINE_ARRAY_SIZE * sizeof(char *));
  char * currentWord = calloc_safe(MAX_LINE_LENGTH, sizeof(char));
  int lineIndex = 1;
  int wordIndex = 0;
  for (int i = 0; current_line->text[i] != '\0'; i++) {
    if(current_line->text[i] != ' ' && current_line->text[i] != '\t' && current_line->text[i] != '\n' && current_line->text[i] != ':' && current_line->text[i] != ',') {
      currentWord[wordIndex] = current_line->text[i];
      wordIndex ++;
    } else {
      if(current_line->text[i] == ':') {
        /* copies ':' to currentWord */
        currentWord[wordIndex] = current_line->text[i];
        wordIndex++;
        /* copies label to first cell in destination arr */
        parsed_line[0] = strndup(currentWord, wordIndex);
        /* reset current word */
        memset(currentWord,0,wordIndex);
        wordIndex = 0;
      } else if(currentWord[0] != '\0') {
        parsed_line[lineIndex] = strndup(currentWord, wordIndex);
        memset(currentWord,0,wordIndex);
        wordIndex = 0;
        lineIndex ++; 
      }
      if(current_line->text[i] == ',') {
        parsed_line[lineIndex] = ",";
        lineIndex ++; 
      } 
    }
  }
  if(currentWord[0] != '\0')
    parsed_line[lineIndex] = strndup(currentWord, wordIndex);
  free(currentWord);
  current_line->parsed_line = parsed_line;
}

line_type get_line_type(line * current_line) {
  // Empty line
  if(current_line->length == 1 || (current_line->length == 2 && (current_line->text[0] == ' ' || current_line->text[0] == '\t'))) return EMPTY_LINE;
  // Comment Line
  if(current_line->text[0] == ';') return COMMENT_LINE;
  // Instruction Line
  if(is_directive(current_line->parsed_line[1])) return INSTRUCTION_LINE;
  if(is_operator(current_line->parsed_line[1])) return COMMAND_LINE;
  return ERROR_LINE;
}

label_type get_inst_type(line * current_line) {
  int i;
  if(strcmp(current_line->parsed_line[1], ".data") == 0) {
    // Checks if label exist, and warns for data inst without label
    if(!current_line->parsed_line[0]) printf("Warning: No label for data instruction in line: %d\n", current_line->line_num);
    // loops over the data for validation
    for(i = 2; i < LINE_ARRAY_SIZE; i++) {
      if(!current_line->parsed_line[i]) break;
      if(i % 2 == 0) {
        int temp = atoi(current_line->parsed_line[i]);
        printf("%d\t", temp);
      } else {
        
      }
    }
    printf("\n");
    return DATA_LABEL;
  }
  if(strcmp(current_line->parsed_line[1], ".string") == 0) {
    return STRING_LABEL;
  }
  if(strcmp(current_line->parsed_line[1], ".struct") == 0) {
    return STRUCT_LABEL;
  }
  if(strcmp(current_line->parsed_line[1], ".entry") == 0) {
    return ENTRY_LABEL;
  }
  if(strcmp(current_line->parsed_line[1], ".extern") == 0) {
    return EXTERN_LABEL;
  }
  return ERROR;
}

opcode get_cmd_type(line * current_line) {

}

address_type get_addr_type(line * current_line) {

}

