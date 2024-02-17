#include "ind_task.h"

int countVowels(struct node_t * start, struct node_t * end) {
	char * vowels = "euioaяюиёеэыуоа";
	node_t * head = start;
	int count = 0;
	while (head != end) {
		for (char * p = vowels; * p != '\0'; p++) {
			if (* p == head->data) {
				count++;
				break;
			}
		}
		head = head->next;
	} 
	return count;
}

void deleteAllWordsWithEvenVowels(list_t * list) {
	node_t * item = list->head;
	if (item == NULL) {
		return;
	}
	while (item->next != NULL) {
		item = item->next;
	}
	char data = item->data;

	item = list->head;
	while (item->data == data) {
		item = item->next;
		if (item == NULL) {
			list->head = NULL;
			return;
		}
		list->head = item;
	}
	
	node_t * last = NULL;
	while (item != NULL) {
		if (item->data == data) {
			node_t * tmp = item;
			last->next = item->next;
			item = tmp->next;
			free(tmp);
		} else {
			last = item;
			item = item->next;
		}
	}

}
