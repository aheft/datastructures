#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

struct Performance *newPerformance(){
    struct Performance *newPerformance = calloc(1, sizeof(struct Performance));
    newPerformance->reads=0;
    newPerformance->writes=0;
    newPerformance->mallocs=0;
    newPerformance->frees=0;
    return (newPerformance);
}

void push(struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width){
    struct Node *ptr=calloc(1, sizeof(struct Node));
    ptr->data=malloc(width);
    memcpy(ptr->data, src, width);
    ptr->next=*list_ptr;
    *list_ptr=ptr;
    performance->mallocs+=1;
    performance->writes+=1;
}

void readHead(struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width){
    if (*list_ptr==NULL){
        fprintf(stderr, "List empty\n");
        exit(0);
    }
    memcpy(dest, (*list_ptr)->data, width);
    performance->reads+=1;
}

void pop(struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width){
    if (*list_ptr==NULL){
        fprintf(stderr, "List empty\n");
        exit(0);
    }
    memcpy(dest, (*list_ptr)->data, width);
    struct Node *temp=(*list_ptr)->next;
    free (*list_ptr);
    *list_ptr=temp;
    performance->reads+=1;
    performance->frees+=1;
}

struct Node **next(struct Performance *performance, struct Node **list_ptr){
    if (*list_ptr==NULL){
        fprintf(stderr, "List empty\n");
        exit(0);
    }
    struct Node **temp=&((*list_ptr)->next);
    performance->reads+=1;
    return temp;
}

int isEmpty(struct Performance *performance, struct Node **list_ptr){
    if (*list_ptr==NULL){
        return (1);
    }
    return (0);
}

void freeList(struct Performance *performance, struct Node **list_ptr){
    while (isEmpty(performance, list_ptr)==0){
        void *temp=malloc(1);
        pop(performance, list_ptr, temp, 1);
        free (temp);
    }
}

void readItem(struct Performance *performance, struct Node **list_ptr, unsigned int index, void *dest, unsigned int width){
    for (int i=0; i<=index; i++){
        if (i==index){
            readHead(performance, list_ptr, dest, width);
            return;
        }
        struct Node **temp=next(performance, list_ptr);
        list_ptr=temp;
    }
}

void appendItem(struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width){
    while (isEmpty(performance, list_ptr)==0){
        struct Node **temp=next(performance, list_ptr);
        list_ptr=temp;
    }
    push(performance, list_ptr, src, width);
}

void insertItem(struct Performance *performance, struct Node **list_ptr, unsigned int index, void *src, unsigned int width){
    for (int i=0; i<=index; i++){
        if (i==index){
            push(performance, list_ptr, src, width);
            return;
        }
        struct Node **temp=next(performance, list_ptr);
        list_ptr=temp;
    }
}

void prependItem(struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width){
    insertItem(performance, list_ptr, 0, src, width);
}

void deleteItem(struct Performance *performance, struct Node **list_ptr, unsigned int index){
    for (int i=0; i<=index; i++){
        if (i==index){
            void *temp=(*list_ptr)->data;
            pop(performance, list_ptr, temp, 10);
            free (temp);
            return;
        }
        struct Node **temp=next(performance, list_ptr);
        list_ptr=temp;
    }
}

int findItem(struct Performance *performance, struct Node **list_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width){
    printf("Entering function %p\n", list_ptr);
    int counter=0;
    struct Node **temp=list_ptr;
    do{
        void *temp2=calloc(200, 1);
        readHead(performance, temp, temp2, width);
        if (compar(temp2, target)==0){
            free (temp2);
            return counter;
        }
        else{
            free (temp2);
            counter++;
            temp=next(performance, temp);
        }
    }
    while (temp!=NULL);
    return (-1);
}