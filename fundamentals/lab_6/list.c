#include "list.h"

void insert(list_t * list, char data) {
    node_t * node = malloc(sizeof(node_t) * 1);
    node->data = data;
    node->next = NULL;
    list->tail->next = node;
    list->tail = node;
}

void freeList(list_t * list) {
	node_t * head = list->head;
	while (head) {
		node_t * tmp = head;
		head = head->next;
		free(tmp);
	}
    free(list);
}

void outputList(list_t * list) {
    node_t * current = list->head;
    while (current) {
        printf("%c", current->data);
        current = current->next;
    }
    printf("\n");
}

list_t * inputList() {

    scanf("%*c");
	char data = getchar();
	if (data == '\n' || data == EOF) {
		return NULL;
	}
	
	list_t * list = malloc(sizeof(list_t) * 1);
    list->head = malloc(sizeof(node_t) * 1);
	list->head->data = data;
	list->head->next = NULL;
	list->tail = list->head;
    
    while (data != '\n' && data != EOF) {
        data = getchar();
        if (data == '\n' || data == EOF) {
            break;
        }

        if (data == ' ' || data == '\t') {
        	if (list->tail->data != '\t' && list->tail->data != ' ') {
        		insert(list, ' ');
        	}
        } else {
			insert(list, data);
		}
	}
    return list;
}