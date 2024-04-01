#include "table.h"

#include "utils.h"

#include "iter.h"

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

Table * createTable(IndexType ksCapacity) {
	Table * table = (Table *) malloc(sizeof(Table) * 1);
	table -> ksCapacity = ksCapacity;
	table -> ksSize = 0;
	
	table -> keySpace = (KeySpace *) malloc(sizeof(KeySpace) * 1);
	table -> keySpace -> entries = (KeyEntry *) malloc(sizeof(KeyEntry) * table -> ksCapacity);

	for (unsigned int i = 0; i < table -> ksCapacity; i++) {
		table -> keySpace -> entries[i].key = NULL;
		table -> keySpace -> entries[i].first = NULL;
	}

	return table;
}

void outputTable(Table * table) {

	char * del = "\n----------------------------------------------\n";

	printf(del);

	if (table == NULL) {
		printf("\nTable is null.\n");
		printf(del);
		return;
	}

	if (table -> ksSize == 0) {
		printf("\nTable is empty.\n");
		printf(del);
		return;
	}

	for (unsigned int i = 0; i < table -> ksSize; i++) {
		KeyEntry entry = table -> keySpace -> entries[i];
		printf("%s:\n", entry.key);

		Node * curNode = entry.first;
		while (curNode != NULL) {
			printf("Val: %s, Rel: %d | ", * curNode -> info, curNode -> release);
			curNode = curNode -> next;
		}
		printf("End.\n");
	}

	printf(del);
	
}

int putKey(Table * table, KeyType key, InfoType info) {
	if (table == NULL || table -> ksSize == table -> ksCapacity) {
		return 0;		
	}

	Node * new = (Node *) malloc(sizeof(Node) * 1);
	new -> info = (InfoType *) malloc(sizeof(InfoType) * 1);
	* new -> info = info;

	Iter * iter = begin(table);

	while (hasNext(iter)) {
		if (strcmp(iter -> current -> key, key) == 0) {
			if (iter -> current -> first == NULL) {
				new -> release = 0;
				new -> next = NULL;
				iter -> current -> first = new;
			} else {
				RelType nextRelease = iter -> current -> first -> release + 1;
				new -> release = nextRelease;
				new -> next = iter -> current -> first;
				iter -> current -> first = new;
			}
			
			free(key);
			free(iter);
			return 1;
		}
		next(iter);
	}

	iter -> current -> key = key;
	
	new -> release = 0;
	new -> next = NULL;
	iter -> current -> first = new;
	table -> ksSize++;

	free(iter);
	return 1;
}

int putKeyWithRelease(Table * table, KeyType key, InfoType info, RelType release) {

	if (table == NULL || table -> ksSize == table -> ksCapacity) {
		return 0;		
	}

	table -> keySpace -> entries[table -> ksSize].key = key;

	Node * new = (Node *) malloc(sizeof(Node) * 1);
	new -> info = (InfoType *) malloc(sizeof(InfoType) * 1);
	* new -> info = info;

	Iter * iter = begin(table);

	while (hasNext(iter)) {
		if (strcmp(iter -> current -> key, key) == 0) {
			if (iter -> current -> first == NULL) {
				new -> release = release;
				new -> next = NULL;
				iter -> current -> first = new;
			} else {
				new -> release = release;
				new -> next = iter -> current -> first;
				iter -> current -> first = new;
			}
			free(iter);
			return 1;
		}
		next(iter);
	}
	
	new -> release = release;
	new -> next = NULL;
	iter -> current -> first = new;
	table -> ksSize++;

	free(iter);
	return 1;
}

Table * findByKey(Table * table, KeyType key) {

	if (table == NULL) {
		return NULL;
	}

	Iter * iter = begin(table);

	while (hasNext(iter)) {
		if (strcmp(key, iter -> current -> key) == 0) {
			Table * resultTable = createTable(TABLE_SIZE);
			Node * curNode = iter -> current -> first;

			if (curNode == NULL) {
				return resultTable;
			}
	
			KeyType dup = m_strdup(key);
			
			while (curNode != NULL) {
				InfoType info_dup = m_strdup(* curNode -> info);
				putKeyWithRelease(resultTable, dup, info_dup, curNode -> release);
				curNode = curNode -> next;	
			}

			free(iter);
			return resultTable;
		}
	}
	
	free(iter);
	return NULL;
}

InfoType * findByKeyAndRelease(Table * table, KeyType key, RelType release) {

	if (table == NULL) {
		return NULL;
	}

	Iter * iter = begin(table);

	while (hasNext(iter)) {
		if (strcmp(key, iter -> current -> key) == 0) {
			Node * curNode = iter -> current -> first;
			while (curNode != NULL) {
				if (curNode -> release == release) {
					free(iter);
					return curNode -> info;
				}
				curNode = curNode -> next;
			}
		}
		next(iter);
	}

	free(iter);
	return NULL;
}

int deleteByKey(Table * table, KeyType key) {

	if (table == NULL) {
		return 0;
	}

	Iter * iter = begin(table);

	while (hasNext(iter)) {
		if (strcmp(key, iter -> current -> key) == 0) {

			free(iter -> current -> key);
			iter -> current -> key = NULL;	
			Node * curNode = iter -> current -> first;
			while (curNode != NULL) {
				Node * tmp = curNode;
				curNode = curNode -> next;
				free(* tmp -> info);
				free(tmp -> info);
				free(tmp);
			}
			
			iter -> current -> first = NULL;

			Iter * last = end(table);

			if (!compare(iter, last)) {
				iter -> current -> key = last -> current -> key;
				iter -> current -> first = last -> current -> first;
				last -> current -> key = NULL;
				last -> current -> first = NULL;
			}

			free(iter);
			free(last);
			table -> ksSize--;
			return 1;
		}
	}

	free(iter);
	return 0;
}

int deleteByKeyAndRelease(Table * table, KeyType key, RelType release) {

	if (table == NULL) {
		return 0;
	}

	for (unsigned int i = 0; i < table -> ksSize; i++) {
		KeyEntry entry = table -> keySpace -> entries[i];
		if (strcmp(key, entry.key) == 0) {

			Node * curNode = entry.first;
			Node * last = NULL;
			while (curNode != NULL) {
				if (curNode -> release == release) {
				
					if (curNode == entry.first) {
						table -> keySpace -> entries[i].first = curNode -> next;
					} else {
						last -> next = curNode -> next;
					}

					curNode->next = NULL;
					
					free(* curNode -> info);
					free(curNode -> info);
					free(curNode);
					
					return 1;
				}
				
				last = curNode;
				curNode = curNode -> next;
			}
		}
	}

	return 0;
}

void freeTable(Table * table) {

	if (table == NULL) {
		return;
	}

	for (unsigned int i = 0; i < table -> ksSize; i++) {
		KeyEntry entry = table -> keySpace -> entries[i];
		free(entry.key);
		Node * curNode = entry.first;
		while (curNode != NULL) {
			Node * tmp = curNode;
			curNode = curNode -> next;
			free(* tmp -> info);
			free(tmp -> info);
			free(tmp);
		}
	}

	free(table -> keySpace -> entries);
	free(table -> keySpace);
	free(table);
}

Table * importFromFile(char * filename) {
	FILE * filePtr = fopen(filename, "r");
	if (filePtr == NULL) {
		return NULL;
	}

	Table * table = createTable(TABLE_SIZE);

	char * s;
	while (strlen((s = file_readline(filePtr)))) {

		char * key = strtok(s, ";");
		
		char * value;
		while ((value = strtok(NULL, ";")) != NULL) {
			char * dup = m_strdup(key);
			putKey(table, dup, m_strdup(value));
		}
		
		free(s);
	}

	free(s);

	fclose(filePtr);
	filePtr = NULL;

	return table;
}
