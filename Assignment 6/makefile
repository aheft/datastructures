$(CC)=gcc -Wall -g -pedantic -std=c99

all: buildidx key2val val2key
	$(CC) buildidx.o -o buildidx; 
	$(CC) key2val.o -o key2val;
	$(CC) val2key.o -o val2key

buildidx: buildidx.c
	$(CC) -c buildidx.c util.c hashfn.c -o buildidx.o 

key2val: key2val.c
	$(CC) -c key2val.c util.c hashfn.c -o key2val.o

val2key: val2key.c
	$(CC) -c val2key.c util.c hashfn.c -o val2key.o

clean:
	rm *.o