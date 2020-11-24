#include "ttt.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>



int main(){
    init_boards();
    init_board(START_BOARD);
    join_graph(START_BOARD);
    return 0;
}