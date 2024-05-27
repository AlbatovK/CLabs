#include "queue.h"

#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include "utils.h"

int queueSize(Queue * q) {
	return q -> size;
}

int frontQueue(Queue * q) {
	return q -> head -> data;
}

int popQueue(Queue * q) {
	if (queueSize(q) == 0) {
		return 0;
	}

	QueueNode * del = q -> head;

	q -> head = q -> head -> next;

	if (q -> head == NULL) {
		q -> tail = NULL;
	}

	int data = del -> data;
	q -> size--;
	free(del);
	return data;
}

void insertQueue(Queue * q, int data) {
	QueueNode * n = (QueueNode *) malloc(sizeof(QueueNode) * 1);
	n -> data = data;
	n -> next = NULL;

	if (queueSize(q) == 0) {
		q -> head = n;
		q -> tail = n;
	} else {
		q -> tail -> next = n;
		q -> tail = n;
	}

	q -> size++;
}

Queue * createQueue() {
	Queue * q = (Queue *) malloc(sizeof(Queue) * 1);
	q -> head = NULL;
	q -> tail = NULL;
	q -> size = 0;
	return q;
}

void eraseQueue(Queue * q) {
	QueueNode * cur = q -> head;
	while (cur) {
		QueueNode * tmp = cur;
		cur = cur -> next;
		free(tmp);
	}

	free(q);
}

