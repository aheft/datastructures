#include "ttt.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char*argv[]){
    init_boards();
    init_board(START_BOARD);
    join_graph(START_BOARD);
    int counter=0;
    for (int i=0; i<HSIZE; i++){
        if (htable[i].init=='1'){
            counter++;
        }
    }
}