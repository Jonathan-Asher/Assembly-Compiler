CC = gcc
FLAGS = -ansi -Wall -pedantic -std=c99 # Flags
OUT = test.out
DEPENDECIES = parser.o

test.out: parser.o
	$(CC) $(FLAGS) -g parser.o -o $(OUT)
	make clean

parser.o: parser.c
	$(CC) $(FLAGS) -c parser.c

# deletes the object files
clean:
	rm $(DEPENDECIES)
