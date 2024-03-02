#include <stdio.h>

#include <stdlib.h>

typedef struct node {
	void * data;
	struct node * next;
} node;

typedef struct queue {
	node * head;
	node * tail;
	int size;
} queue;


int is_queue_empty(queue * q) {
	return q->head == NULL;
}

int size(queue * q) {
	return q->size;
}

void * pop(queue * q) {

	if (is_queue_empty(q)) {
		return NULL;
	}

	node * del = q->head;
	
	q->head = q->head->next;
	
	if (q->head == NULL) {
		q->tail = NULL;
	}

	void * data = del->data;
	free(del);
	q->size--;
	return data;

}

void insert(queue * q, void * data) {
	node * n = (node *) malloc(sizeof(node) * 1);
	n->data = data;
	n->next = NULL;
	q->size++;

	if (is_queue_empty(q)) {
		q->head = n;
		q->tail = n;
	} else {
		q->tail->next = n;
		q->tail = n;
	}
}


void insert_min_to_tail(queue * q, int min_index) {
	void * min_val = NULL;
	int n = q->size;
	for (int i = 0; i < n; i++) {
		void * curr = pop(q);
		if (i != min_index)
			insert(q, curr);
		else min_val = curr;
	}
	insert(q, min_val);
}

int min_index(queue * q, int sorted_index, int (*pred)(const void *, const void *) ) {
	int m_i = -1;
	void * min_val = NULL;
	int n = q->size;
	for (int i = 0; i < n; i++) {
		void * curr = pop(q);
		if ((min_val == NULL || pred(curr, min_val) == -1) && i <= sorted_index) {
			m_i = i;
			min_val = curr;
		} 
		insert(q, curr);
	}
	return m_i;
}

void sort(queue * q, int (*pred)(const void *, const void *) ) {
	for (int i = 1; i <= q->size; i++) {
		int m_i = min_index(q, q->size - i, pred);
		insert_min_to_tail(q, m_i);
	}
}

void for_each(queue * q, int (*pred)(const void *) ) {
	 node * cur = q->head;
	 while (cur != NULL) {
	 	pred(cur->data); 
	 	cur = cur->next;
	 }
}

queue * create_new_queue() {
    queue * q = (queue *) malloc(sizeof(queue) * 1);
    q -> head = NULL;
    q -> tail = NULL;
    q -> size = 0;
    return q;
}

void erase_queue(queue * q) {
	 node * cur = q->head;
	 while (cur != NULL) {
	 	node * tmp = cur; 
	 	cur = cur->next;
	 	free(tmp);
	 }
    free(q);
}
