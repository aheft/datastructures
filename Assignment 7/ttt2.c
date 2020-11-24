#include "ttt.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

void init_boards(){
    for (int i=0; i<HSIZE; i++){
        htable[i].init='0';
    }
}

int depth(Board board){
    int hash=board_hash(board);
    struct BoardNode node=htable[hash];
    return node.depth;
}

char winner(Board board){
    int hash=board_hash(board);
    struct BoardNode node=htable[hash];
    return node.winner;
}

char turn(Board board){
    int hash=board_hash(board);
    struct BoardNode node=htable[hash];
    return node.turn;
}

void init_board(Board board){
    int hash=board_hash(board);
    htable[hash].init='1';
    htable[hash].turn=turn(board);
    htable[hash].depth=depth(board);
    strcpy(htable[hash].board, board);
    htable[hash].winner=winner(board);
}

void join_graph(Board board){
    int hash=board_hash(board);
    for (int i=0; i<9; i++){
        if (board[pos2idx[i]]=='X' || board[pos2idx[i]]=='O'){
            htable[hash].move[i]=-1;
        }
        else{
            char newboard[30]="";
            strcpy(newboard, "");
            char currentturn=turn(board);
            strcpy(newboard, board);
            newboard[pos2idx[i]]=currentturn;
            int newhash=board_hash(newboard);
            htable[newhash].move[i]=newhash;
            if (htable[newhash].init=='0'){
                init_board(newboard);
                join_graph(newboard);
            }
        }
    }
}

void compute_score(){
    return;
}

int best_move(int board){
    return 0;
}