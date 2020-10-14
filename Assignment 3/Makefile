CFLAGS= -std=c99 -Wall -pedantic
CC=gcc

all: list test1 test2 test3

list: list.o list.h 
	$(CC) $(CFLAGS) -c list.c -o list.o

test1: test1.o list.o
	$(CC) $(CFLAGS) test1.o list.o -o test1

test1.o: test1.c list.h
	$(CC) $(CFLAGS) -c test1.c -o test1.o

test2: test2.o list.o
	$(CC) $(CFLAGS) test2.o list.o -o test2

test2.o: test2.c list.h
	$(CC) $(CFLAGS) -c test2.c -o test2.o

test3: test3.o list.o
	$(CC) $(CFLAGS) test3.o list.o -o test3

test3.o: test3.c list.h
	$(CC) $(CFLAGS) -c test3.c -o test3.o

clean:
	rm *.o