CC = gcc
FLAGS = -ansi -Wall -pedantic -std=c99 # Flags
OUT = test.out
DEPENDECIES = line_parser.o util.o

test.out: $(DEPENDECIES)
	$(CC) $(FLAGS) -g $(DEPENDECIES) -o $(OUT)
	make clean

line_parser.o: line_parser.c
	$(CC) $(FLAGS) -c line_parser.c

util.o: util.c
	$(CC) $(FLAGS) -c util.c

# deletes the object files
clean:
	rm $(DEPENDECIES)
