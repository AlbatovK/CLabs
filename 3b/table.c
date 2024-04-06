#include "table.h"

#include <stdlib.h>

#include <stdio.h>

#include <string.h>

int hashHorner(KeyType key, int tableSize, int hash_key) {
	int hash = 0;

	if (key == NULL) {
		return hash;
	}
	
	for (unsigned int i = 0; i < strlen(key); i++) {
		hash = (key[i] + hash_key * hash) % tableSize;
	}

	return (hash * 2 + 1) % tableSize;
}

int hash_1(KeyType key) {
	return hashHorner(key, TABLE_SIZE, 31 * (TABLE_SIZE - 1));
}

int hash_2(KeyType key) {
	return hashHorner(key, TABLE_SIZE, 29 * (TABLE_SIZE + 1));
}

Table * createTable(int mSize) {

	Table * table = (Table *) malloc(sizeof(Table) * 1);
	table -> mSize = mSize;
	table -> cSize = 0;
	table -> entries = (KeyEntry *) malloc(sizeof(KeyEntry) * table -> mSize);

	for (unsigned int i = 0; i < table -> mSize; i++) {
		table -> entries[i].key = NULL;
		table -> entries[i].busy = 0;
		table -> entries[i].release = 0;
		table -> entries[i].info = NULL;
	}

	return table;
}

void freeTable(Table * table) {
	if (table == NULL) {
		return;
	}

	for (unsigned int i = 0; i < table -> mSize; i++) {
		KeyEntry entry = table -> entries[i];
		if (entry.key != NULL && entry.busy) {
			free(entry.key);
			free(entry.info);
		}
	}

	free(table -> entries);
	free(table);
	
}

KeyEntry * searchByKey(Table * table, KeyType key, int * n) {

	if (table == NULL || table -> cSize == table -> mSize) {
		return 0;
	}

	int x = hash_1(key);
	int y = hash_2(key);

	int res_size = 0;

	for (unsigned int i = 0; i < table -> mSize; i++) {
		KeyEntry entry = table -> entries[x];
		if (entry.key != NULL && strcmp(entry.key, key) == 0 && entry.busy) {
			res_size += 1;
		}

		x = (x + y) % TABLE_SIZE;
	}

	* n = res_size;

	if (res_size == 0) {
		return 0;
	}
	
	x = hash_1(key);
	y = hash_2(key);

	KeyEntry * res_arr = (KeyEntry *) malloc(sizeof(KeyEntry) * res_size);

	int j = 0;
	for (unsigned int i = 0; i < table -> mSize; i++) {
		KeyEntry entry = table -> entries[x];
		if (entry.key != NULL && strcmp(entry.key, key) == 0 && entry.busy) {
			res_arr[j] = entry;
			j++;
		}

		x = (x + y) % TABLE_SIZE;
	}

	return res_arr;
	
}

KeyEntry * searchByKeyAndRelease(Table * table, KeyType key, RelType release) {

	if (table == NULL || table -> cSize == table -> mSize) {
		return 0;
	}

	int x = hash_1(key);
	int y = hash_2(key);

	for (unsigned int i = 0; i < table -> mSize; i++) {
		KeyEntry entry = table -> entries[x];

		if (entry.key != NULL && strcmp(entry.key, key) == 0 && entry.busy && entry.release == release) {
			return table -> entries + x;
		}

		x = (x + y) % TABLE_SIZE;
	}

	return 0;

}

void outputTable(Table * table) {

	if (table == NULL || table -> cSize == 0) {
		printf("Table is empty.\n");
		return;
	}

	for (unsigned i = 0; i < table -> mSize; i++) {
		KeyEntry entry = table -> entries[i];
		if (!entry.busy) {
			continue;
		}
		
		printf("%s : %d (%d)\n", entry.key, entry.info -> value, entry.release);
		
	}
	
}

int deleteByKey(Table * table, KeyType key) {

	if (table == NULL || table -> cSize == table -> mSize) {
		return 0;
	}

	int x = hash_1(key);
	int y = hash_2(key);

	for (unsigned int i = 0; i < table -> mSize; i++) {
		KeyEntry entry = table -> entries[x];

		if (entry.key != NULL && !entry.busy && strcmp(entry.key, key) == 0) {
			free(entry.key);
			entry.key = NULL;
			free(entry.info);
			entry.info = NULL;
			entry.busy = 0;
			entry.release = 0;
			return 1;
		}

		x = (x + y) % TABLE_SIZE;
		
	}

	return 0;
}


int putKey(Table * table, KeyType key, int value) {

	if (table == NULL || table -> cSize == table -> mSize) {
		return 0;
	}
	
	int x = hash_1(key);
	int y = hash_2(key);

	int release = 0;
	for (unsigned int i = 0; i < table -> mSize; i++) {
		KeyEntry entry = table -> entries[x];
		
		if (entry.key == NULL || entry.busy == 0) {
			table -> entries[x].key = key;
			table -> entries[x].busy = 1;
			table -> entries[x].release = release;
			InfoType * info = (InfoType *) malloc(sizeof(InfoType) * 1);
			info -> value = value;
			table -> entries[x].info = info;
			table -> cSize++;
			return 1;
			
		} else if (strcmp(entry.key, key) == 0) {
			release++;
		}

		x = (x + y) % table -> mSize;
	}

	return 0;
}
