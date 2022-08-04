#ifndef LINE_PARSER_H
#define LINE_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "enums.h"
#include "utils.h"

void parse_line(line * currentLine);

line_type get_line_type(line * currentLine);
label_type get_inst_type(line * currentLine);
opcode get_cmd_type(line * currentLine);
address_type get_addr_type(line * currentLine);

#endif
