CFLAGS= -std=c99 -Wall -pedantic
CC=gcc

all: list

list: list.c list.h 
	$(CC) $(CFLAGS) -c list.c -o list.o

listtest: list.c list.h test.c
	$(CC) $(CFLAGS) *.c -o list

clean:
	rm *.o