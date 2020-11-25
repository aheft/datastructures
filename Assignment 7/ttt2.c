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

void setturn(Board board){
    int hash=board_hash(board);
    struct BoardNode node=htable[hash];
    int counter=0;
    for (int i=0; i<9; i++){
        if (board[pos2idx[i]]=='X' || board[pos2idx[i]]=='O'){
            counter++;
        }
    }
    if (counter==9){
        htable[hash].turn='-';
    }
    else if (counter%2==0){
        htable[hash].turn='X';
    }
    else{
        htable[hash].turn='O';
    }
}

void setdepth(Board board){
    int hash=board_hash(board);
    struct BoardNode node=htable[hash];
    int counter=0;
    for (int i=0; i<9; i++){
        if (board[pos2idx[i]]=='X' || board[pos2idx[i]]=='O'){
            counter++;
        }
    }
    htable[hash].depth=counter;
}

void init_board(Board board){
    int hash=board_hash(board);
    htable[hash].init='1';
    setturn(board);
    setdepth(board);
    strcpy(htable[hash].board, board);
    setwinner(board);
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

int boardfull(Board board){
    for (int i=0; i<9; i++){
        if (board[pos2idx[i]]!='X' && board[pos2idx[i]]!='O'){
            return 0;
        }
    }
    return 1;
}

void setwinner(Board board){
    int index=board_hash(board);
    if (calcrow(board, 'X')==1 || calccol(board, 'X')==1 || calcdiag(board, 'X')==1){
        htable[index].winner='X';
        return;
    }
    if (calcrow(board, 'O')==1 || calccol(board, 'O')==1 || calcdiag(board, 'O')==1){
        htable[index].winner='O';
        return;
    }
    if (boardfull(board)){
        htable[index].winner='-';
        return;
    }
    else{
        htable[index].winner='?';
        return;
    }
}

void setmoves(Board board){
    int hashidx=board_hash(board);
    for (int i=0; i<9; i++){
        if (board[pos2idx[i]]!='X' && board[pos2idx[i]]!='O'){
            htable[hashidx].move[i]=i;
        }
        else{
            htable[hashidx].move[i]=-1;
        }
    }
}

void compute_score(){
    for (int i=0; i<HSIZE; i++){
        setwinner(htable[i].board);
        char won=winner(htable[i].board);
        if (won=='X'){
            htable[i].score=1;
        }
        else if (won=='O'){
            htable[i].score=-1;
        }
        else if (won=='-'){
            htable[i].score=0;
        }
        else{
            setmoves(htable[i].board);
            if (htable[i].turn=='X'){
                for (int j=8; j>=0; j--){
                    if (htable[i].move[j]!=-1){
                        htable[i].score=htable[i].move[j];
                    }
                }
            }
            else{
                for (int j=0; j<9; j++){
                    if (htable[i].move[j]!=-1){
                        htable[i].score=htable[i].move[j];
                    }
                }
            }
        }
    }
}

int best_move(int board){
    return 0;
}