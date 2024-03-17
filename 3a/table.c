#include "table.h"

#include "utils.h"

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

	table -> keySpace -> entries[table -> ksSize].key = key;

	Node * new = (Node *) malloc(sizeof(Node) * 1);
	new -> info = (InfoType *) malloc(sizeof(InfoType) * 1);
	* new -> info = info;

	for (unsigned int i = 0; i < table -> ksSize; i++) {
		KeyEntry entry = table -> keySpace -> entries[i];
		if (strcmp(entry.key, key) == 0) {
			if (table -> keySpace -> entries[i].first == NULL) {
				new -> release = 0;
				new -> next = NULL;
				table -> keySpace -> entries[i].first = new;
			} else {
				RelType nextRelease = table -> keySpace -> entries[i].first -> release + 1;
				new -> release = nextRelease;
				new -> next = table -> keySpace -> entries[i].first;
				table -> keySpace -> entries[i].first = new;
			}
			return 1;
		}
	}
	
	new -> release = 0;
	new -> next = NULL;
	table -> keySpace -> entries[table -> ksSize].first = new;
	table -> ksSize++;

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

	for (unsigned int i = 0; i < table -> ksSize; i++) {
		KeyEntry entry = table -> keySpace -> entries[i];
		if (strcmp(entry.key, key) == 0) {
			if (table -> keySpace -> entries[i].first == NULL) {
				new -> release = release;
				new -> next = NULL;
				table -> keySpace -> entries[i].first = new;
			} else {
				new -> release = release;
				new -> next = table -> keySpace -> entries[i].first;
				table -> keySpace -> entries[i].first = new;
			}
			return 1;
		}
	}
	
	new -> release = release;
	new -> next = NULL;
	table -> keySpace -> entries[table -> ksSize].first = new;
	table -> ksSize++;

	return 1;
}

Table * findByKey(Table * table, KeyType key) {

	if (table == NULL) {
		return NULL;
	}

	for (unsigned int i = 0; i < table -> ksSize; i++) {
		KeyEntry entry = table -> keySpace -> entries[i];
		if (strcmp(key, entry.key) == 0) {
			Table * resultTable = createTable(TABLE_SIZE);
			Node * curNode = entry.first;

			if (curNode == NULL) {
				return resultTable;
			}
	
			KeyType dup = m_strdup(key);
			
			while (curNode != NULL) {
				InfoType info_dup = m_strdup(* curNode -> info);
				putKeyWithRelease(resultTable, dup, info_dup, curNode -> release);
				curNode = curNode -> next;	
			}

			return resultTable;
		}
	}
	
	return NULL;
}

InfoType * findByKeyAndRelease(Table * table, KeyType key, RelType release) {

	if (table == NULL) {
		return NULL;
	}

	for (unsigned int i = 0; i < table -> ksSize; i++) {
		KeyEntry entry = table -> keySpace -> entries[i];
		if (strcmp(key, entry.key) == 0) {
			Node * curNode = entry.first;
			while (curNode != NULL) {
				if (curNode -> release == release) {
					return curNode -> info;
				}
				curNode = curNode -> next;
			}
		}
	}
	
	return NULL;
}

int deleteByKey(Table * table, KeyType key) {

	if (table == NULL) {
		return 0;
	}

	for (unsigned int i = 0; i < table -> ksSize; i++) {
		KeyEntry entry = table -> keySpace -> entries[i];
		if (strcmp(key, entry.key) == 0) {

			free(entry.key);
			entry.key = NULL;	
			Node * curNode = entry.first;
			while (curNode != NULL) {
				Node * tmp = curNode;
				curNode = curNode -> next;
				free(* tmp -> info);
				free(tmp -> info);
				free(tmp);
			}
			
			entry.first = NULL;

			if (i != table -> ksSize - 1) {
				table -> keySpace -> entries[i].key = table -> keySpace -> entries[table -> ksSize - 1].key;
				table -> keySpace -> entries[i].first = table -> keySpace -> entries[table -> ksSize - 1].first;
				table -> keySpace -> entries[table -> ksSize - 1].key = NULL;
				table -> keySpace -> entries[table -> ksSize - 1].first = NULL;
			}

			table -> ksSize--;
			return 1;
		}
	}

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
		char * dup = strdup(key);
		
		char * value;
		while ((value = strtok(NULL, ";")) != NULL) {
			putKey(table, dup, m_strdup(value));
		}
		
		free(s);
	}

	free(s);

	fclose(filePtr);
	filePtr = NULL;

	return table;
}
