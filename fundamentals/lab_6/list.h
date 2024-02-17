#ifndef LIST_H

#define LIST_H

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

typedef struct node_t {
    struct node_t * next;
    char data;
} node_t;

typedef struct list_t {
    node_t * head;
    node_t * tail;
} list_t;

void insert(list_t *, char);

void freeList(list_t *);

void outputList(list_t *);

list_t * inputList();

#endif