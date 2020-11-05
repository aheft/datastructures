#ifndef HASH
#define HASH

struct HashTable{
    unsigned int capacity;
    unsigned int nel;
    void **data;
    int (*hash)(void *, int );
    int (*compar)(const void *, const void *);
};

struct Performance{
    unsigned int reads;
    unsigned int writes;
    unsigned int mallocs;
    unsigned int frees;
};

struct HashTable *createTable(struct Performance *performance, unsigned int capacitty, int (*hash)(void *, int), int (*compar)(const void *, const void *));

void addElement(struct Performance *performance, struct HashTable *table, void *src);

int getIdx(struct Performance *performance, struct HashTable *table, void *src);

void freeTable(struct Performance *performance, struct HashTable *table);

void *getElement(struct Performance *performance, struct HashTable *table, void *src);

void removeElement(struct Performance *performance, struct HashTable *table, void *target);

#endif