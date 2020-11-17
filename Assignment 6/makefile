$(CC)=gcc -Wall -g -pedantic -std=c99

all: buildidx key2val val2key
	$(CC) buildidx.o util.o hashfn.o -o buildidx; 
	$(CC) key2val.o util.o hashfn.o -o key2val;
	$(CC) val2key.o util.o hashfn.o -o val2key

util: util.c
	$(CC) -c util.c -o util.o 
	
hashfn: hashfn.c
	$(CC) -c hashfn.c -o hashfn.o 

buildidx: buildidx.c util hashfn
	$(CC) -c buildidx.c -o buildidx.o 

key2val: key2val.c util hashfn
	$(CC) -c key2val.c -o key2val.o

val2key: val2key.c util hashfn
	$(CC) -c val2key.c -o val2key.o

clean:
	rm *.o