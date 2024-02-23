#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue * queue_t;

int do_queue(queue_t);

queue_t create_new_queue();

void erase_queue(queue_t);

#endif