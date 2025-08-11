programa: main.o parser.c scanner.c
	gcc -o programa main.o scanner.c parser.c -L/usr/lib -lfl

main.o: main.c parser.h scanner.h
	gcc -c main.c

parser.c parser.h: parser.y
	bison parser.y

scanner.c scanner.h: scanner.l
	flex scanner.l

clean:
	rm -f *.o programa parser.c scanner.c parser.h scanner.h
