#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>

#include <stdlib.h>

typedef struct queue * queue_t;

int do_queue(queue_t q);

queue_t create_new_queue();

#endif