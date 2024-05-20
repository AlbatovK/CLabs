#ifndef QUEUE_H
#define QUEUE_H

#include "tree.h"

typedef struct NodeMetaData {

	TreeNode * node;
	
	int level;
	
} NodeMetaData;

typedef struct QueueNode {

	NodeMetaData * data;
	
	struct QueueNode * next;
	
} QueueNode;

typedef struct Queue {

	QueueNode * head;
	
	QueueNode * tail;
	
	int size;
	
} Queue;

int sizeQueue(Queue *);

NodeMetaData * frontQueue(Queue *);

NodeMetaData * popQueue(Queue *);

void insertQueue(Queue *, NodeMetaData *);

Queue * createQueue();

void eraseQueue(Queue *);

#endif
