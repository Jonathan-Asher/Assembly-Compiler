
#include "file_parser.h"

int parse_file(char * filename) {
  line * current_line = malloc_safe(sizeof(line));
  FILE * fp, * fp2;
  char * dest_filename = malloc_safe(strlen(filename) * sizeof(char));
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  int line_num = 1;
  int i;

  char ** arr = malloc_safe(LINE_ARRAY_SIZE * sizeof(char *));

  strncpy(dest_filename, filename, strlen(filename) - 4);
  dest_filename[strlen(filename) - 4] = '\0';
  strcat(dest_filename, "_no_macro.txt");

  fp = fopen(filename, "r");
  fp2 = fopen(dest_filename, "wr");
  if (fp == NULL)
    exit(1);
  
  macro_func(fp, fp2);

  fclose(fp);
  fclose(fp2);

  fp = fopen(dest_filename, "r");
  while ((read = getline(&line, &len, fp)) != -1) {
    strcpy(current_line->text, line);
    current_line->length = read;
    current_line->line_num = line_num;
    /* line_type type; */
    printf("%d: [%d] %s\n", current_line->line_num, current_line->length, current_line->text);
    parse_line(current_line, arr);
    for (i = 0; i < LINE_ARRAY_SIZE; i++) {
      if(arr[i])
        printf("%d: '%s' ", i+1, arr[i]);
    }
    memset(arr,0,LINE_ARRAY_SIZE * sizeof(char *));
    printf("\n");
    line_num ++;
  }

  fclose(fp);
  if (line)
      free(line);
  exit(0);
}
