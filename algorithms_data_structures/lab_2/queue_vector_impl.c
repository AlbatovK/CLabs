#include <stdio.h>

#include <stdlib.h>

typedef struct queue {
    int a;
    int b;
} queue;

int do_queue(queue * q) {
    q->a = 13;
    printf("a - %d", q->a);
    return 0;
}

queue * create_new_queue() {
    return (queue *) malloc(sizeof(queue) * 1);
}