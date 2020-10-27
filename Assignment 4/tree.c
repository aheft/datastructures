#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"

struct Performance *newPerformance(){
    struct Performance *newPerformance = calloc(1, sizeof(struct Performance));
    newPerformance->reads=0;
    newPerformance->writes=0;
    newPerformance->mallocs=0;
    newPerformance->frees=0;
    return (newPerformance);
}

void attachNode(struct Performance *performance, struct Node **node_ptr, void *src, unsigned int width){
    struct Node *ptr=calloc(1, sizeof(struct Node));
    ptr->data=malloc(width);
    memcpy(ptr->data, src, width);
    ptr->lt=NULL;
    ptr->gte=NULL;
    *node_ptr=ptr;
    performance->mallocs+=1;
    performance->writes+=1;
}

int comparNode(struct Performance *performance, struct Node **node_ptr, int (*compar)(const void*, const void *), void *target){
    performance->reads+=1;
    return (compar(target, (*node_ptr)->data));
}

struct Node **next(struct Performance *performance, struct Node **node_ptr, int direction){
    if (*node_ptr==NULL){
        fprintf(stderr, "Tree empty\n");
        exit(0);
    }
    performance->reads+=1;
    if (direction<0){
        return (&(*node_ptr)->lt);
    }
    else{
        return (&(*node_ptr)->gte);
    }
}

void readNode(struct Performance *performance, struct Node **node_ptr, void *dest, unsigned int width){
    if (*node_ptr==NULL){
        fprintf(stderr, "Tree empty\n");
        exit(0);
    }
    memcpy(dest, (*node_ptr)->data, width);
    performance->reads+=1;
}

void detachNode (struct Performance *performance, struct Node **node_ptr){
    if (*node_ptr==NULL){
        fprintf(stderr, "Tree empty\n");
        exit(0);
    }
    free (*node_ptr);
    *node_ptr=NULL;
    performance->frees+=1;
}

int isEmpty(struct Performance *performance, struct Node **node_ptr){
    if (*node_ptr==NULL){
        return (1);
    }
    else{
        return (0);
    }
}

void addItem(struct Performance *performance, struct Node **node_ptr, int (*compar)(const void*, const void *), void *src, unsigned int width){
    struct Node *ptr= *node_ptr;
    while (ptr!=0){
        ptr=next(performance, &ptr, comparNode(performance, &ptr, compar, src));
    }
    attachNode(performance, &ptr, src, width);
}

void freeTree(struct Performance *performance, struct Node **node_ptr){
    while (isEmpty(performance, node_ptr)==0){
        detachNode(performance, node_ptr);
        next(performance, node_ptr, 1);
    }
}