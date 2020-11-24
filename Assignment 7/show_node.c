#include "ttt.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[]){
    if (argc>1){
        for (int i=1; i<argc; i++){
            int hash=atoi(argv[i]);
            init_boards();
            init_board(START_BOARD);
            join_graph(START_BOARD);
            print_node(htable[hash]);
        }
    }
}