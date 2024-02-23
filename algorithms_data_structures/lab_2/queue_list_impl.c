#include <stdio.h>

#include <stdlib.h>

typedef struct queue {
    int a;
    int b;
} queue;

int do_queue(queue * q) {
    q->b = 13;
    printf("b - %d", q->b);
    return 0;
}

queue * create_new_queue() {
    return (queue *) malloc(sizeof(queue) * 1);
}