#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define TABLE_SIZE 100

char * m_strcat(char * s1, char * s2) {
	int l1 = strlen(s1);
	int l2 = strlen(s2);

	char * s3 = malloc(sizeof(char) * (l1 + l2 + 1));
	
	memcpy(s3, s1, l1);
	memcpy(s3 + l1, s2, l2 + 1);
	
	return s3;
}

char * m_strdup(char * s) {
	char * res = (char *) malloc(sizeof(char) * (strlen(s) + 1));
	unsigned int i;
	for (i = 0; i < strlen(s); i++) {
		res[i] = s[i];
	}
	res[i] = '\0';
	return res;
}

char * readline() {
	char s[82] = {0};
	char * res = malloc(sizeof(char) * 1);
	res[0] = '\0';

	int in = scanf("%81[^\n]", s);
	if (in == 0) {
		scanf("%*c");
		in = scanf("%81[^\n]", s);
	}
	
	while (in > 0) {
		char * tmp = res;
		res = m_strcat(s, res);
		free(tmp);
		in = scanf("%81[^\n]", s);
	}
	
	return res;
}

char * file_readline(FILE * file_ptr) {
	char s[81] = {0};
	char * res = malloc(sizeof(char) * 1);
	res[0] = '\0';
	
	int in = fscanf(file_ptr, "%81[^\n]", s);
	if (in == 0) {
		fscanf(file_ptr, "%*c");
		in = fscanf(file_ptr, "%81[^\n]", s);
	}
	while (in > 0) {

		char * tmp = res;
		res = m_strcat(s, res);
		free(tmp);

		in = fscanf(file_ptr, "%81[^\n]", s);
	}
	
	return res;
}

typedef int RelType;

typedef unsigned int IndexType;

typedef char * InfoType;

typedef char * KeyType;

typedef struct Node {
	RelType release;
	InfoType * info;
	struct Node * next;
} Node;

typedef struct KeyEntry {
	KeyType key;
	Node * first;
} KeyEntry;

typedef struct KeySpace {
	KeyEntry * entries;
} KeySpace;

typedef struct Table {
	KeySpace * keySpace;
	IndexType ksCapacity;
	IndexType ksSize;	
} Table;


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

int getInt(int * a) {
	int n;
	do {
		n = scanf("%d", a);
		if (n < 0) {
			return 0;
		}

		if (n == 0) {
			printf("Invalid input. Enter again.\n");
			scanf("%*c");	
		}
		
	} while (n == 0);

	return 1;
}


int main() {
	Table * table = createTable(TABLE_SIZE);
	int action = 0;

	while (action != 8) {

		printf("Enter action. 1 - put key, 2 - delete by key, 3 - delete by key and release.\n");
		printf("4 - import table from csv file, 5 - output table, 6 - find by key, 7 - find by key and release.\n");
		printf("8 - exit program.\n");

		char * pr = "";
		do {
			printf("%s", pr);
			getInt(&action);	
			pr = "No such action. Enter again.\n";
		} while(action < 1 || action > 8);

		switch(action) {

			case 1:
				printf("Enter key:\n");
				char * keyToPut = readline();
				printf("Enter value:\n");
				char * value = readline();
				
				int resPut = putKey(table, keyToPut, value);

				if (resPut == 0) {
					printf("Unable to put key in table. Table is full or equals to null.\n");
					free(keyToPut);
					free(value);
					break;
				}

				printf("Successfully put key: %s, value: %s.\n", keyToPut, value);
				break;
				
			case 2:
				printf("Enter key:\n");
				char * keyToDel = readline();

				int resDel = deleteByKey(table, keyToDel);

				if (resDel == 0) {
					printf("Cannot delete because table is null or key is not present in table.\n");
					free(keyToDel);
					break;
				}

				printf("Successfully deleted key: %s from table.\n", keyToDel);
				free(keyToDel);
				break;

			case 3:

				printf("Enter key:\n");
				char * keyToDelWithRel = readline();

				int release;
				printf("Enter release:\n");
				getInt(&release);
				
				int resDelWithRel = deleteByKeyAndRelease(table, keyToDelWithRel, release);

				if (resDelWithRel == 0) {
					printf("Cannot delete because table is null, key is not present in table or it has no such release.\n");
					free(keyToDelWithRel);
					break;
				}

				printf("Successfully deleted key: %s from table.\n", keyToDelWithRel);
				free(keyToDelWithRel);
				break;
			
				
			case 4:
				printf("Enter filename:\n");
				char * filename = readline();
				Table * tableFromFile = importFromFile(filename);
				
				if (tableFromFile == NULL) {
					printf("Unable to read table from this file. Try again.\n");
					freeTable(tableFromFile);
					free(filename);
					break;
				}
				
				freeTable(table);
				free(filename);
				table = tableFromFile;
				break;

			case 5:

				outputTable(table);
				break;

			case 6:
				printf("Enter key:\n");
				char * keyToFind = readline();

				Table * foundTable = findByKey(table, keyToFind);

				printf("Result Table:\n");
				outputTable(foundTable);

				freeTable(foundTable);

				free(keyToFind);
				break;
				
			case 7:

				printf("Enter key:\n");
				char * keyToFindWithRel = readline();

				int releaseToFind;
				printf("Enter release:\n");
				getInt(&releaseToFind);
				
				InfoType * found = findByKeyAndRelease(table, keyToFindWithRel, releaseToFind);

				if (found == NULL) {
					printf("No entris found with key: %s and release: %d.\n", keyToFindWithRel, releaseToFind);
				} else {
					printf("Found entry: key: %s, value: %s, release: %d.\n", keyToFindWithRel, * found, releaseToFind);
				}

				free(keyToFindWithRel);
				break;
				
			case 8:
				printf("Exiting.\n");
				break;
		}
	}
	
	freeTable(table);
	return 0;
	
}
