#include "ttt.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>



int main(){
    init_boards();
    join_graph(START_BOARD);
    print_node(htable[board_hash(START_BOARD)]);
    START_BOARD[pos2idx[0]]='X';
    print_node(htable[board_hash(START_BOARD)]);
    START_BOARD[pos2idx[8]]='O';
    START_BOARD[pos2idx[1]]='X';
    START_BOARD[pos2idx[7]]='O';
    START_BOARD[pos2idx[2]]='X';
    print_node(htable[board_hash(START_BOARD)]);
    return 0;
}