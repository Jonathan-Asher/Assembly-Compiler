gssCC = gcc
FLAGS = -ansi -Wall -pedantic -std=c99# Flags
OUT = test.out
DEPENDECIES = assembler.o macro_parser.o line_parser.o file_parser.o utils.o

test.out: $(DEPENDECIES)
	$(CC) $(FLAGS) -g $(DEPENDECIES) -o $(OUT)
	make clean

assembler.o: assembler.c
	$(CC) $(FLAGS) -c assembler.c

macro_parser.o: macro_parser.c
	$(CC) $(FLAGS) -c macro_parser.c

line_parser.o: line_parser.c
	$(CC) $(FLAGS) -c line_parser.c

file_parser.o: file_parser.c
	$(CC) $(FLAGS) -c file_parser.c

utils.o: utils.c
	$(CC) $(FLAGS) -c utils.c

# deletes the object files
clean:
	rm $(DEPENDECIES)
