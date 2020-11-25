#include "ttt.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>



int main(){
    init_boards();
    init_board(START_BOARD);
    printf("%d\n", calccol(START_BOARD, 'X'));
    return 0;
}