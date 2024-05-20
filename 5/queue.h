#ifndef QUEUE_H
#define QUEUE_H

typedef struct QueueNode {
	int data;
	struct QueueNode * next;
} QueueNode;

typedef struct Queue {
	QueueNode * head;
	QueueNode * tail;
	int size;
} Queue;

int queueSize(Queue * q);

int frontQueue(Queue * q);

int popQueue(Queue * q);

void insertQueue(Queue * q, int data);

Queue * createQueue();

void eraseQueue(Queue * q);

#endif



