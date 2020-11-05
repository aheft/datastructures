#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

struct Performance *newPerformance(){
    struct Performance *newPerformance = calloc(1, sizeof(struct Performance));
    newPerformance->reads=0;
    newPerformance->writes=0;
    newPerformance->mallocs=0;
    newPerformance->frees=0;
    return (newPerformance);
}

struct HashTable *createTable(struct Performance *performance, unsigned int capacity, int (*hash)(void *, int), int (*compar)(const void *, const void *)){
    struct HashTable *newTable=malloc(sizeof(struct HashTable));
    if(newTable == NULL){
        fprintf(stderr, "Malloc failed.");
        exit(0);
    }
    newTable->capacity=capacity;
    newTable->hash=hash;
    newTable->compar=compar;
    newTable->nel=0;
    newTable->data=malloc(capacity*4);
    if(newTable->data == NULL){
        fprintf(stderr, "Malloc failed.");
        exit(0);
    }
    for (int i=0; i<capacity; i++){
        newTable->data[i]=NULL;
    }
    performance->reads+=capacity;
    performance->mallocs++;
    return newTable;
}

void addElement(struct Performance *performance, struct HashTable *table, void *src){
    if (table->nel==table->capacity){
        printf("Length has reached capacity.");
        exit(0);
    }
    else{
        int index=table->hash(src, table->capacity);
        for (index; table->data[index]!=NULL; index++){
            if (index==table->capacity){
                index=0;
            }
            performance->reads++;
        }
        table->data[index]=src;
        table->nel++;
        performance->writes++;
    }
}

int getIdx(struct Performance *performance, struct HashTable *table, void *src){
    int index=table->hash(src, table->capacity);
    int oindex=index;
    for (index; table->compar(src, table->data[index])!=0; index++){
        if (index==table->capacity){
            index=0;
        }
        if (index==oindex-1){
            return (-1);
        }
        performance->reads++;
    }
    return(index);
}

void freeTable(struct Performance *performance, struct HashTable *table){
    free (table->data);
    free (table);
    performance->frees++;
}

void *getElement(struct Performance *performance, struct HashTable *table, void *src){
    if (getIdx(performance, table, src)==-1){
        return NULL;
    }
    else{
        return (table->data[getIdx(performance, table, src)]);
    }
}

void removeElement(struct Performance *performance, struct HashTable *table, void *target){
    table->data[getIdx(performance, table, src)]=NULL;
    performance->writes++;
    table->nel-=1;
}