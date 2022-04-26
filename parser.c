#include "parser.h"

// test
int main() {
  line * cr = malloc(sizeof(line));
  strcpy(cr->text, "a, , , ");
  char ** arr = malloc(LINE_ARRAY_SIZE);
  parseLine(cr, arr);
  for (int i = 0; i < 6; i++) {
    printf("%d: %s\n", i+1, arr[i]);
  }
  return 0;
}

void parseLine(line * currentLine, char ** dest) {
  char * currentWord = calloc((MAX_LINE_LENGTH + 1) * sizeof(char), (MAX_LINE_LENGTH + 1) * sizeof(char));
  int lineIndex = 1;
  int wordIndex = 0;
  for (int i = 0; currentLine->text[i] != '\0'; i++) {
    if(currentLine->text[i] != ' ' && currentLine->text[i] != '\t' && currentLine->text[i] != ':' && currentLine->text[i] != ',') {
      currentWord[wordIndex] = currentLine->text[i];
      wordIndex ++;
    } else {
      if(currentLine->text[i] == ':') {
        dest[0] = strndup(currentWord, wordIndex);
        memset(currentWord,0,wordIndex);
        wordIndex = 0;
        dest[lineIndex] = ":";
        lineIndex ++; 
      } else if(currentWord[0] != '\0') {
        printf("* %c *", currentLine->text[i]);
        dest[lineIndex] = strndup(currentWord, wordIndex);
        memset(currentWord,0,wordIndex);
        wordIndex = 0;
        lineIndex ++; 
      }
      if(currentLine->text[i] == ',') {
        printf("! %c !", currentLine->text[i]);
        dest[lineIndex] = ",";
        lineIndex ++; 
      }
      
    }
  }
  if(currentWord[0] != '\0')
    dest[lineIndex] = strndup(currentWord, wordIndex);
  free(currentWord);
}
