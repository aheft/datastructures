$(CC)=gcc -Wall -g -pedantic -std=c99

all: alphatoe count_nodes ttt1 ttt2
	$(CC) alphatoe.o ttt1.o ttt2.o -o alphatoe;
	$(CC) count_nodes.o ttt1.o ttt2.o -o count_nodes;
	$(CC) show_node.o ttt1.o ttt2.o -o show_node

test: testmain.c ttt2.c ttt1.c
	$(CC) testmain.c ttt2.c ttt1.c -o testmain

alphatoe: alphatoe.c ttt1 ttt2
	$(CC) -c alphatoe.c -o alphatoe.o

count_nodes: count_nodes.c ttt1 ttt2
	$(CC) -c count_nodes.c -o count_nodes.o

show_node: show_node.c ttt1 ttt2
	$(CC) -c show_node.c -o show_node.o

ttt1: ttt1.c
	$(CC) -c ttt1.c -o ttt1.o

ttt2: ttt2.c
	$(CC) -c ttt2.c -o ttt2.o

clean:
	rm *.o