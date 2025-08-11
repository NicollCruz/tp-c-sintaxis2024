programa: main.o scanner 
	gcc -o programa main.o scanner.c -L/usr/lib -lfl

main.o: main.c tokens.h
	gcc -c main.c

scanner: scanner.l
	flex scanner.l


clean:
	rm *.o scanner.c scanner.h programa

