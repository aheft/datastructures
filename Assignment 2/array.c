#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "array.h"

struct Performance *newPerformance(){
    struct Performance *newPerformance = calloc(1, sizeof(struct Performance));
    newPerformance->reads=0;
    newPerformance->writes=0;
    newPerformance->mallocs=0;
    newPerformance->frees=0;
    return (newPerformance);
}

struct Array *newArray(struct Performance *performance, unsigned int width, unsigned int capacity){
    struct Array *newArray=calloc(1, sizeof(struct Array));
    newArray->width=width;
    newArray->capacity=capacity;
    newArray->nel=0;
    newArray->data=calloc(width*capacity, 1);
    performance->mallocs+=1;
    return (newArray);
}

void readItem (struct Performance *performance, struct Array *array, unsigned int index, void *dest){
    if(index>=array->nel){
        fprintf(stderr, "Index out of bounds");
        exit (0);
    }
    //copy certain number of bytes (array width) from array data offset by index to destination.
    int offset = index*array->width;
    memcpy(dest, array->data+offset, array->width);
    performance->reads+=1;
}

void writeItem(struct Performance *performance, struct Array *array, unsigned int index, void *src){
    if(index>array->nel || index>=array->capacity){
        fprintf(stderr, "Index out of bounds");
        exit (0);
    }
    memcpy(array->data+(index*array->width), src, array->width);
    if (index==array->nel){
        array->nel+=1;
    }
    performance->writes+=1;
}

void contract (struct Performance *performance, struct Array *array){
    if(array->nel==0){
        fprintf(stderr, "Array error");
        exit (0);
    }
    array->nel-=1;
}

void freeArray(struct Performance *performance, struct Array *array){
    free (array->data);
    free (array);
    performance->frees+=1;
}

void appendItem(struct Performance *performance, struct Array *array, void *src){
    writeItem(performance, array, array->nel, src);
}

void insertItem(struct Performance *performance, struct Array *array, unsigned int index, void *src){
    for (int i=array->nel-1; i>=index; i--){
        readItem(performance, array, i, array->data[i+1]);
    }
    writeItem(performance, array, index, src);
}

void prependItem(struct Performance *performance, struct Array *array, void *src){
    insertItem(performance, array, 0, src);
}

void deleteItem(struct Performance *performance, struct Array *array, unsigned int index){
    for (int i=index+1; i<array->nel; i++){
        readItem(performance, array, i-1, array->data[i]);
    }
    contract(performance, array);
}

int main(){
    struct Performance *perf=newPerformance();
    struct Array *arr=newArray(perf, sizeof(int), 10);
    int *a=calloc(5, sizeof(int));
    for (i=0; i<5; i++){
        a[i]=i+1;
    }
    writeItem(perf, arr, 0, a);
    int *temp=arr->data;
    printf("%d\n", temp[0]);
    return 0;
}