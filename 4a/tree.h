#ifndef TREE_H
#define TREE_H

typedef struct InfoField {

	int value;

	struct InfoField * next;
	
} InfoField;

typedef struct TreeNode {

	InfoField * infoNode;
	
	int key;

	struct TreeNode * prev;

	struct TreeNode * left;

	struct TreeNode * right;
	
} TreeNode;

void insert(TreeNode * * node, int key, int value, TreeNode * prev);

void printBinaryTree(TreeNode * node);

TreeNode * delete(TreeNode * * node, int key);

TreeNode * importFromFile(char * filename);

TreeNode * findNearestByKey(TreeNode * root, int key);

TreeNode * search(TreeNode * node, int key);

void freeTree(TreeNode * node);

TreeNode * processFile(char * filename, char * output);

void specialSearch(TreeNode * node, int digits);

void dot_print_tree(TreeNode * root, char * filename);

void std_print_tree(TreeNode * root, int offset);

InfoField * searchByKeyAndPos(TreeNode * node, int key, int pos);

#endif
