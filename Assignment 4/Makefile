CFLAGS= -std=c99 -Wall -pedantic
CC=gcc

all: tree ttest

tree: tree.o tree.h 
	$(CC) $(CFLAGS) -c tree.c -o tree.o

ttest: ttest.o tree.o
	$(CC) $(CFLAGS) ttest.o tree.o -o ttest

ttest.o: ttest.c tree.h
	$(CC) $(CFLAGS) -c ttest.c -o ttest.o

clean:
	rm *.o