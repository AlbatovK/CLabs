#ifndef TABLE_H

#define TABLE_H

#define TABLE_SIZE 100

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

Table * createTable(IndexType ksCapacity);

void outputTable(Table * table);

int putKey(Table * table, KeyType key, InfoType info);

int putKeyWithRelease(Table * table, KeyType key, InfoType info, RelType release);

Table * findByKey(Table * table, KeyType key);

InfoType * findByKeyAndRelease(Table * table, KeyType key, RelType release);

int deleteByKey(Table * table, KeyType key);

int deleteByKeyAndRelease(Table * table, KeyType key, RelType release);

void freeTable(Table * table);

Table * importFromFile(char * filename);

#endif
