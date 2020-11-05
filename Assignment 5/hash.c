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
    newTable->data=malloc(sizeof(void*)*capacity);
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
        int i;
        for (i = index; table->data[index]!=NULL; i++){
            if (i==table->capacity){
                i=0;
            }
            performance->reads++;
        }
        table->data[i]=src;
        table->nel++;
        performance->writes++;
    }
}

int getIdx(struct Performance *performance, struct HashTable *table, void *src){
    int index=table->hash(src, table->capacity);
    int oindex=index;
    int i;
    for (i=index; table->compar(src, table->data[index])!=0; i++){
        if (i==table->capacity){
            i=0;
        }
        if (i==oindex-1){
            return (-1);
        }
        performance->reads++;
    }
    return(i);
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
    table->data[getIdx(performance, target, table)]=NULL;
    performance->writes++;
    table->nel-=1;
}