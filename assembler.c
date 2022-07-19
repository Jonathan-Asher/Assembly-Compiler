#include "file_parser.h"
#include "macro_parser.h"
#include "line_parser.h"
#include "utils.h"

int main(int argc, char * argv[]) {
  /* line * cr = malloc_safe(sizeof(line));
  strcpy(cr->text, "LABEL: .data 1,2,3,4,5");
  char ** arr = malloc_safe(LINE_ARRAY_SIZE * sizeof(char *));
  parse_line(cr, arr);
  for (int i = 0; i < LINE_ARRAY_SIZE; i++) {
    printf("%d: %s\n", i+1, arr[i]);
  }
  return 0; */
  if(argc == 1) {
    printf("Error: expected one argument.");
    exit(1);
  }
  for(int i = 1; i < argc; i++) {
    parse_file(argv[i]);
  }
}

