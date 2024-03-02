#ifndef QUEUE_H

#define QUEUE_H
 
typedef struct queue * queue_t;

void * pop(queue_t);

void insert(queue_t, void *);

int is_queue_empty(queue_t);

queue_t create_new_queue();

void erase_queue(queue_t);

int size(queue_t);

void sort(queue_t, int (*pred)(const void *, const void *) );

void for_each(queue_t, void (*pred)(const void *) );

#endif
