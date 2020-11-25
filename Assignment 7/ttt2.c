#include "ttt.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

int calcrow(Board board, char c){
    int counter=0;
    for (int i=0; i<3; i++){
        if (board[pos2idx[i]]==c){
            counter++;
        }
    }
    if (counter==3){
        return 1;
    }
    counter=0;
    for (int i=3; i<6; i++){
        if (board[pos2idx[i]]==c){
            counter++;
        }
    }
    if (counter==3){
        return 1;
    }
    counter=0;
    for (int i=6; i<9; i++){
        if (board[pos2idx[i]]==c){
            counter++;
        }
    }
    if (counter==3){
        return 1;
    }
    counter=0;
    return 0;
}

int calccol(Board board, char c){
    int counter=0;
    for (int i=0; i<9; i+=3){
        if (board[pos2idx[i]]==c){
            counter++;
        }
    }
    if (counter==3){
        return 1;
    }
    counter=0;
    for (int i=1; i<9; i+=3){
        if (board[pos2idx[i]]==c){
            counter++;
        }
    }
    if (counter==3){
        return 1;
    }
    counter=0;
    for (int i=2; i<9; i+=3){
        if (board[pos2idx[i]]==c){
            counter++;
        }
    }
    if (counter==3){
        return 1;
    }
    counter=0;
    return 0;
}

int calcdiag(Board board, char c){
    int counter=0;
    for (int i=0; i<9; i+=4){
        if (board[pos2idx[i]]==c){
            counter++;
        }
    }
    if (counter==3){
        return 1;
    }
    counter=0;
    for (int i=2; i<7; i+=2){
        if (board[pos2idx[i]]==c){
            counter++;
        }
    }
    if (counter==3){
        return 1;
    }
    counter=0;
}

//void compute_score(){
  //  if ()
//}