#include <stdio.h>

#include <stdlib.h>

#define QUEUE_SIZE 100

typedef struct queue {
	int head;
	int tail;
	void * * vector;
	int size;
} queue;

void sort(queue * q, int (*pred)(const void *, const void *) ) {
	for (int i = q->head; i < q->tail - 1; i++) {
		for (int j = q->head; j < q->tail - i - 1; j++) {
			if (pred(q->vector[j], q->vector[j + 1]) == 1) {
				void * tmp = q->vector[j + 1];
				q->vector[j + 1] = q->vector[j];
				q->vector[j] = tmp;
			}
		}
	}
}

void for_each(queue * q, void (*pred)(const void *) ) {
	for (int i = q->head; i < q->tail; i++) {
		pred(q->vector[i]);
	}
}

int is_queue_empty(queue * q) {
	return q->size == 0;
}

int size(queue * q) {
	return q->size;
}

void insert(queue * q, void * data) {
	q->vector[q->tail] = data;
	q->tail = (q->tail + 1) % QUEUE_SIZE;
	q->size++;
}

void * pop(queue * q) {
	if (is_queue_empty(q)) {
		return NULL;
	}
	void * data = q->vector[q->head];
	q->head = (q-> head + 1) % QUEUE_SIZE;
	q->size--;
	return data;
}

queue * create_new_queue() {
    queue * q = (queue *) malloc(sizeof(queue) * 1);
    q -> vector = (void * *) malloc(sizeof(void *) * QUEUE_SIZE);
    q -> head = 0;
    q -> tail = 0;
    q -> size = 0;
    return q;
}

void erase_queue(queue * q) {
	free(q->vector);
    free(q);
}
