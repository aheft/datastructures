CFLAGS= -std=c99 -Wall -pedantic
CC=gcc

all: hash htest1

hash: hash.o hash.h 
	$(CC) $(CFLAGS) -c hash.c -o hash.o

htest1: htest1.o hash.o
	$(CC) $(CFLAGS) htest1.o hash.o -o htest1

htest1.o: htest1.c hash.h
	$(CC) $(CFLAGS) -c htest1.c

clean:
	rm *.o