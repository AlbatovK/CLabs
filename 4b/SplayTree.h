#ifndef SPLAY_TREE_H

#define SPLAY_TREE_H

typedef char * KeyType;

typedef char * ValueType;

typedef struct InfoType {
	ValueType value;
	struct InfoType * next;
} InfoType;

typedef struct SplayTreeNode {
	char * key;
	InfoType * infoNode;
	struct SplayTreeNode * left, * right, * parent;	
} SplayTreeNode;

typedef enum SplayType {
	ZIG, ZIG_ZIG, ZIG_ZAG, NONE
} SplayType;	

typedef struct SplaySplitResult {
	SplayTreeNode * left, * right;
	int found;
} SplaySplitResult;

SplayTreeNode * find(SplayTreeNode * node, KeyType key);

SplayTreeNode * insertNode(SplayTreeNode * * root, KeyType key);

SplayTreeNode * removeNode(SplayTreeNode * * root, KeyType key);

void printTreeHorizontal(SplayTreeNode * root);

void freeTree(SplayTreeNode * node);

void dotPrintTree(SplayTreeNode * root, char * filename);

SplayTreeNode * findMinNode(SplayTreeNode * root);

#endif
