#include "table.h"

#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include "utils.h"

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

int hash_1(KeyType key, int tableSize) {
	return hashHorner(key, tableSize, 31 * (tableSize - 1));
}

int hash_2(KeyType key, int tableSize) {
	return hashHorner(key, tableSize, 29 * (tableSize + 1));
}

int isPrime(int i) {

	for (int j = 2; j * j <= i; j++) {
		if (i % j == 0) {
			return 0;
		}
	}
	
	return 1;
}

int nextPrime(int n) {
	int i = n + 2;
	while (!isPrime(i)) {
		i += 2;
	}

	return i;
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

	int x = hash_1(key, table -> mSize);
	int y = hash_2(key, table -> mSize);

	int res_size = 0;

	for (unsigned int i = 0; i < table -> mSize; i++) {
		KeyEntry entry = table -> entries[x];
		if (entry.key != NULL && strcmp(entry.key, key) == 0 && entry.busy) {
			res_size += 1;
		}

		x = (x + y) % table -> mSize;
	}

	* n = res_size;

	if (res_size == 0) {
		return 0;
	}
	
	x = hash_1(key, table -> mSize);
	y = hash_2(key, table -> mSize);

	KeyEntry * res_arr = (KeyEntry *) malloc(sizeof(KeyEntry) * res_size);

	int j = 0;
	for (unsigned int i = 0; i < table -> mSize; i++) {
		KeyEntry entry = table -> entries[x];
		if (entry.key != NULL && strcmp(entry.key, key) == 0 && entry.busy) {
			res_arr[j] = entry;
			j++;
		}

		x = (x + y) % table -> mSize;
	}

	return res_arr;
	
}

KeyEntry * searchByKeyAndRelease(Table * table, KeyType key, RelType release) {

	if (table == NULL || table -> cSize == table -> mSize) {
		return 0;
	}

	int x = hash_1(key, table -> mSize);
	int y = hash_2(key, table -> mSize);

	for (unsigned int i = 0; i < table -> mSize; i++) {
		KeyEntry entry = table -> entries[x];

		if (entry.key != NULL && strcmp(entry.key, key) == 0 && entry.busy && entry.release == release) {
			return table -> entries + x;
		}

		x = (x + y) % table -> mSize;
	}

	return 0;

}

void outputTable(Table * table) {

	printf("\n");

	if (table == NULL || table -> cSize == 0) {
		printf("Table is empty.\n");
		printf("\n");
		return;
	}

	for (unsigned i = 0; i < table -> mSize; i++) {
		KeyEntry entry = table -> entries[i];
		if (!entry.busy) {
			continue;
		}
		
		printf("%s : %d (%d)\n", entry.key, entry.info -> value, entry.release);
		
	}

	printf("\n");
	
}

int deleteByKey(Table * table, KeyType key) {

	if (table == NULL || table -> cSize == table -> mSize) {
		return 0;
	}

	int x = hash_1(key, table -> mSize);
	int y = hash_2(key, table -> mSize);

	int deleted = 0;
	for (unsigned int i = 0; i < table -> mSize; i++) {
		KeyEntry entry = table -> entries[x];

		if (entry.key != NULL && entry.busy && strcmp(entry.key, key) == 0) {
			free(entry.key);
			table -> entries[x].key = NULL;
			free(entry.info);
			table -> entries[x].info = NULL;
			table -> entries[x].busy = 0;
			table -> entries[x].release = 0;
			table -> cSize--;
			deleted++;
		}

		x = (x + y) % table -> mSize;
		
	}

	return deleted > 0 ? 1 : 0;
}


Table * importFromFile(char * filename) {

	FILE * file = fopen(filename, "rb");

	if (file == NULL) {
		return NULL;
	}

	Table * table = createTable(TABLE_START_SIZE);

	int n;
	fread(&n, sizeof(int), 1, file);

	for (int i = 0; i < n; i++) {
		int keyLen;
		fread(&keyLen, sizeof(int), 1, file);
		char * key = (char *) malloc(sizeof(char) * (keyLen + 1));
		fread(key, sizeof(char), keyLen, file);
		key[keyLen] = '\0';

		int value;
		fread(&value, sizeof(int), 1, file);
		putKey(&table, key, value);
	}

	fclose(file);

	return table;
}

int exportToFile(Table * table, char * filename) {

	FILE * file = fopen(filename, "wb");

	if (file == NULL || filename == NULL || table == NULL) {
		return 0;
	}

	fwrite(&(table -> cSize), sizeof(int), 1, file);

	for (int i = 0; i < (int) table -> mSize; i++) {
		KeyEntry entry = table -> entries[i];
		if (entry.key == NULL || !entry.busy) {
			continue;
		}
		
		int len = strlen(entry.key);
		fwrite(&len, sizeof(int), 1, file);
		fwrite(entry.key, sizeof(char), strlen(entry.key), file);
		int value = entry.info -> value;
		fwrite(&value, sizeof(int), 1, file);
	}

	fclose(file);
	
	return 1;
}

Table * rehash(Table * table) {
	int nextSize = nextPrime(table -> mSize);

	Table * new = createTable(nextSize);

	for (int i = 0; i < (int) table -> mSize; i++) {
		KeyEntry entry = table -> entries[i];
		if (entry.key == NULL || !entry.busy) {
			continue;
		}

		putKey(&new, m_strdup(entry.key), entry.info -> value);
		
	}
	
	freeTable(table);

	return new;
	
}

int putKey(Table * * table, KeyType key, int value) {

	 if (table == NULL) {
		return 0;
	 }

	 if ((*table) -> cSize == (*table) -> mSize) {
	 	* table = rehash(*table);
	 }

	int x = hash_1(key, (*table) -> mSize);
	int y = hash_2(key, (*table) -> mSize);

	int release = 0;
	for (unsigned int i = 0; i < (*table) -> mSize; i++) {
		KeyEntry entry = (*table) -> entries[x];
		
		if (entry.key == NULL || entry.busy == 0) {
			(*table) -> entries[x].key = key;
			(*table) -> entries[x].busy = 1;
			(*table) -> entries[x].release = release;
			InfoType * info = (InfoType *) malloc(sizeof(InfoType) * 1);
			info -> value = value;
			(*table) -> entries[x].info = info;
			(*table) -> cSize++;
			return 1;
			
		} else if (strcmp(entry.key, key) == 0) {
			release++;
		}

		x = (x + y) % (*table) -> mSize;
	}

	* table = rehash(*table);

	 x = hash_1(key, (*table) -> mSize);
		 y = hash_2(key, (*table) -> mSize);
	
		 release = 0;
		for (unsigned int i = 0; i < (*table) -> mSize; i++) {
			KeyEntry entry = (*table) -> entries[x];
			
			if (entry.key == NULL || entry.busy == 0) {
				(*table) -> entries[x].key = key;
				(*table) -> entries[x].busy = 1;
				(*table) -> entries[x].release = release;
				InfoType * info = (InfoType *) malloc(sizeof(InfoType) * 1);
				info -> value = value;
				(*table) -> entries[x].info = info;
				(*table) -> cSize++;
				return 1;
				
			} else if (strcmp(entry.key, key) == 0) {
				release++;
			}
	
			x = (x + y) % (*table) -> mSize;
		}
	
}
