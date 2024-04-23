#include "queue.h"

#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include "utils.h"

int sizeQueue(Queue * q) {
	return q -> size;
}

NodeMetaData * frontQueue(Queue * q) {
	return q -> head -> data;
}

NodeMetaData * popQueue(Queue * q) {
	if (sizeQueue(q) == 0) {
		return NULL;
	}

	QueueNode * del = q -> head;

	q -> head = q -> head -> next;

	if (q -> head == NULL) {
		q -> tail = NULL;
	}

	NodeMetaData * data = del -> data;
	free(del);
	q -> size--;
	return data;
}

void insertQueue(Queue * q, NodeMetaData * data) {
	QueueNode * n = (QueueNode *) malloc(sizeof(QueueNode) * 1);
	n -> data = data;
	n -> next = NULL;

	if (sizeQueue(q) == 0) {
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
	while (cur != NULL) {
		QueueNode * tmp = cur;
		cur = cur -> next;
		free(tmp -> data);
		free(tmp);
	}
	free(q);
}
