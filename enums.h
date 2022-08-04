#ifndef ENUMS_H
#define ENUMS_H

typedef enum opcode {
  /* 2 Operators */
  MOV_OP = 0,
	CMP_OP = 1,
	ADD_OP = 2,
	SUB_OP = 3,
	LEA_OP = 6,
	/* 1 Operators */
	NOT_OP = 4,
	CLR_OP = 5,
	INC_OP = 7,
	DEC_OP = 8,
	JMP_OP = 9,
	BNE_OP = 10,
	GET_OP = 11,
	PRN_OP = 12,
	JSR_OP = 13,
	/* 0 Operators */
	RTS_OP = 14,
	HLT_OP = 15,
	ERROR_OP = -1
} opcode;

typedef enum booleans {
	FALSE = 0, TRUE = 1
} bool;

typedef enum ARE {
  ABSOLUTE = 0,
  EXTERNAL = 1,
  RELOCATABLE = 2,
} ARE;

typedef enum registers {
  R0,
  R1,
  R2,
  R3,
  R4,
  R5,
  R6,
  R7
} registers;

typedef enum address_type {
  ERROR_ADDRESS = -1,
  IMMEDIATE_ADDRESS, // 1 additional word
  DIRECT_ADDRESS, // 1 additional word
  STRUCT_ADDRESS, // 2 additional word
  DIRECT_REGISTER_ADDRESS // 1 additional word
} address_type;

typedef enum label_type {
  ERROR_LABEL,
  DATA_LABEL,
  STRING_LABEL,
  STRUCT_LABEL,
  ENTRY_LABEL,
  EXTERN_LABEL,
  CODE_LABEL
} label_type;

typedef enum line_type {
  ERROR_LINE,
  EMPTY_LINE,
  COMMENT_LINE,
  INSTRUCTION_LINE,
  COMMAND_LINE
} line_type;

#endif
