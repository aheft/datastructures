#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, char *argv[]){
    struct Performance *performance=newPerformance();
    struct Node *thelist=NULL;
    int a=12;
    push (performance, &thelist, &a, sizeof(int));
    int b=0;
    readHead(performance, &thelist, &b, sizeof(int));
    printf("testing push, readhead\n");
    printf("%d\n", b);
}