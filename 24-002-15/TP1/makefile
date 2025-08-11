CC = gcc
CFLAGS = -g -Wall -c -pedantic-errors -std=c2x 

.PHONY: clean run

programa: main.o tabla.o conversion.o
	$(CC) main.o tabla.o conversion.o -o programa

main.o: main.c tabla.h
	$(CC) $(CFLAGS) main.c -o main.o

tabla.o: tabla.c tabla.h conversion.h
	$(CC) $(CFLAGS) $< -o $@

conversion.o: conversion.c conversion.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm main.o mate.o programa

run: programa
	./programa

###############################################################################################
programa: main.o tabla.o conversion.o
	gcc -o programa main.o tabla.o conversion.o

main.o: main.c tabla.h
	gcc -c main.c

tabla.o: tabla.c tabla.h conversion.h
	gcc -c tabla.c

conversion.o: conversion.c conversion.h
	gcc -c conversion.c

clean:
	rm *.o programa

