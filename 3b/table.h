#ifndef TABLE_H

#define TABLE_H

#define TABLE_START_SIZE 5

typedef unsigned int IndexType;

typedef int BusyType;

typedef char * KeyType;

typedef unsigned int RelType;

typedef struct InfoType {
	int value;	
}  InfoType;

typedef struct KeyEntry {
	BusyType busy;
	KeyType key;
	RelType release;
	InfoType * info;
} KeyEntry;

typedef struct Table {
	KeyEntry * entries;
	IndexType mSize;
	IndexType cSize;
} Table;

Table * createTable(int);

void freeTable(Table *);

void outputTable(Table *);

int putKey(Table * *, KeyType, int);

KeyEntry * searchByKey(Table *, KeyType, int *);

KeyEntry * searchByKeyAndRelease(Table * table, KeyType, RelType);

int deleteByKey(Table * table, KeyType);

Table * importFromFile(char *);

int exportToFile(Table *, char *);

#endif
