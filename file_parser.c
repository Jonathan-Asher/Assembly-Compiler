
#include "file_parser.h"

int dc, ic;
data_image dimg;
code_image cimg;
symbol_table symblos;
bool error_flag = FALSE;
char last_error[80];

int parse_file(char * filename) {
  line * current_line = malloc_safe(sizeof(line));
  FILE * fp, * fp2;
  char * dest_filename = malloc_safe(strlen(filename) * sizeof(char));
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  int line_num = 1;
  int i;
  bool labelExists=false;
  symbol_table a1;
  a1.head=NULL;



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
    printf("line %d: [%d] %s\n", current_line->line_num, current_line->length, current_line->text);
    parse_line(current_line);
    for (i = 0; i < LINE_ARRAY_SIZE; i++) {
      if(current_line->parsed_line[i])
        printf("\tcell [%d]: '%s' ", i+1, current_line->parsed_line[i]);
    }
    current_line->type = get_line_type(current_line);

    if(validLabel(current_line->parsed_line[0])){
      labelExists=true;
    }

    switch (current_line->type)
    {
    case INSTRUCTION_LINE:
      label_type ltype = get_inst_type(current_line);
      add_label(current_line->parsed_line[0], dc, label_type, a1)

    case COMMAND_LINE:
      label_type ltype = get_cmd_type(current_line);
    case ERROR_LINE:
    default:
      break;
    }


    printf("\n type %d \n", current_line->type);
    if(current_line->type == 3) {
      label_type ltype = get_inst_type(current_line);
      printf("label type %d \n", ltype);
    }
    line_num ++;
  }

  fclose(fp);
  if (line)
      free(line);
  exit(0);
}
