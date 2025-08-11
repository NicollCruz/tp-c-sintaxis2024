CC = gcc
CFLAGS = -g -Wall -c -pedantic-errors -std=c2x

.PHONY: clean run

parser.c parser.h: parser.y
	bison -d parser.y

scanner.c scanner.h: scanner.l
	flex scanner.l

programa: main.o parser.o scanner.o semantic.o symbol.o
	$(CC) main.o scanner.o parser.o symbol.o semantic.o -o programa

main.o: main.c parser.h scanner.h
	$(CC) $(CFLAGS) main.c -o main.o

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) parser.c -o parser.o

scanner.o: scanner.c scanner.h
	$(CC) $(CFLAGS) scanner.c -o scanner.o

semantic.o: semantic.c symbol.h
	$(CC) $(CFLAGS) semantic.c -o semantic.o

symbol.o: symbol.c symbol.h
	$(CC) $(CFLAGS) symbol.c -o symbol.o

clean:
	rm -f main.o parser.o parser.c parser.h scanner.o scanner.c scanner.h semantic.o symbol.o mainok.c programa

run: programa
	./programa
