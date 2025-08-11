programa: main.o parser.o scanner.o
	gcc -o programa main.o parser.o scanner.o

main.o: main.c parser.h
	gcc -c main.c
	
parser.o: parser.c parser.h scanner.h
	gcc -c parser.c

scanner.o: scanner.c scanner.h
	gcc -c scanner.c

clean:
	rm *.o programa

