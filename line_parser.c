#include "line_parser.h"

/* test */
/* int main() {
  line * cr = malloc_safe(sizeof(line));
  strcpy(cr->text, "LABEL: .data 1,2,3,4,5");
  char ** arr = malloc_safe(LINE_ARRAY_SIZE * sizeof(char *));
  parseLine(cr, arr);
  for (int i = 0; i < LINE_ARRAY_SIZE; i++) {
    printf("%d: %s\n", i+1, arr[i]);
  }
  return 0;
} */

void parse_line(line * currentLine, char ** dest) {
  char * currentWord = calloc_safe(MAX_LINE_LENGTH, sizeof(char));
  int lineIndex = 1;
  int wordIndex = 0;
  for (int i = 0; currentLine->text[i] != '\0'; i++) {
    if(currentLine->text[i] != ' ' && currentLine->text[i] != '\t' && currentLine->text[i] != ':' && currentLine->text[i] != ',') {
      currentWord[wordIndex] = currentLine->text[i];
      wordIndex ++;
    } else {
      if(currentLine->text[i] == ':') {
        /* copies ':' to currentWord */
        currentWord[wordIndex] = currentLine->text[i];
        wordIndex++;
        /* copies label to first cell in destination arr */
        dest[0] = strndup(currentWord, wordIndex);
        /* reset current word */
        memset(currentWord,0,wordIndex);
        wordIndex = 0;
      } else if(currentWord[0] != '\0') {
        dest[lineIndex] = strndup(currentWord, wordIndex);
        memset(currentWord,0,wordIndex);
        wordIndex = 0;
        lineIndex ++; 
      }
      if(currentLine->text[i] == ',') {
        dest[lineIndex] = ",";
        lineIndex ++; 
      } 
    }
  }
  if(currentWord[0] != '\0')
    dest[lineIndex] = strndup(currentWord, wordIndex);
  free(currentWord);
}
