#include "tree.h"

#include <stdio.h>

#include <string.h>

#include <ctype.h>

#include <stdlib.h>

#include "queue.h"

#include "utils.h"

NodeMetaData * createNodeMetaData(TreeNode * node, int level) {
	NodeMetaData * data = (NodeMetaData *) malloc(sizeof(NodeMetaData) * 1);
	data -> node = node;
	data -> level = level;
	return data;
}

int maxDepth(TreeNode * node) {

	if (node == NULL) {
		return 0;
	}

	return 1 + (maxDepth(node -> right) > maxDepth(node -> left) ? maxDepth(node -> right) : maxDepth(node -> left)); 
}

void printBinaryTree(TreeNode * root) {

	int depth = maxDepth(root);

	int last = 0;
	int offset = (1 << depth) - 1;

	Queue * q = createQueue();
	NodeMetaData * data = createNodeMetaData(root, last);
	insertQueue(q, data);

	while (sizeQueue(q)) {
		
		NodeMetaData nd = * frontQueue(q);
		
		if (last != nd.level) {
			printf("\n");
			last = nd.level;
			offset = (1 << (depth - nd.level)) - 1;
		}

		if (nd.node != NULL) {
			printf(" %*s%d%*s", offset, " ", nd.node -> key, offset, " ");			
		} else {
			printf(" %*s", offset << 1, " ");
		}

		if (nd.node != NULL) {
		
			NodeMetaData * dl = createNodeMetaData(nd.node -> left, last + 1);
			NodeMetaData * dr = createNodeMetaData(nd.node -> right, last + 1);
			
			insertQueue(q, dl);
			insertQueue(q, dr);
		}

		NodeMetaData * data = popQueue(q);
		free(data);
		
	}
	printf("\n");
	eraseQueue(q);
}

InfoField * createInfoField(int value) {
	InfoField * info = (InfoField *) malloc(sizeof(InfoField) * 1);
	info -> value = value;
	info -> next = NULL;
	return info;
}

TreeNode * createNode(TreeNode * left, TreeNode * right, TreeNode * prev, int key) {
	TreeNode * node = (TreeNode *) malloc(sizeof(TreeNode) * 1);
	node -> left = left;
	node -> right = right;
	node -> prev = prev;
	node -> key = key;
	node -> infoNode = NULL;
	return node;
}

void freeNode(TreeNode * node) {

	if (node == NULL) {
		return;
	}

	InfoField * cur = node -> infoNode;
	while (cur) {
		InfoField * tmp = cur -> next;
		free(cur);
		cur = tmp;
	}
	
	free(node);
	
}

TreeNode * minInSubTree(TreeNode * node) {

	if (node == NULL) {
		return NULL;
	}

	if (node -> left == NULL) {
		return node;
	}

	return minInSubTree(node -> left);
}

TreeNode * maxInSubTree(TreeNode * node) {

	if (node -> right == NULL) {
		return node;
	}

	return maxInSubTree(node -> right);
}


void insert(TreeNode * * node, int key, int value, TreeNode * prev) {
	if (* node == NULL) {
		InfoField * info = createInfoField(value);
		* node = createNode(NULL, NULL, prev, key);
		(* node) -> infoNode = info;
	} else {
		if ( (* node) -> key == key) {
			InfoField * info = createInfoField(value);
			InfoField * infoNode = (* node) -> infoNode;
			info -> next = infoNode;
			(* node) -> infoNode = info;
		} else {
			if (key < (* node) -> key) {
				insert(&( (* node) -> left), key, value, *node);
			} else if (key > (* node) -> key) {
				insert(&( (* node) -> right), key, value, *node);
			}
		}
	}
}

TreeNode * delete(TreeNode * * node, int key) {
	if (* node == NULL) {
		return NULL;
	}
	
	if (key < (* node) -> key) {
		TreeNode * deleted = delete(&((* node) -> left), key);
		(* node) -> left = deleted;
	} else if (key > (* node) -> key) {
		TreeNode * deleted = delete(&((* node) -> right), key);
		(* node) -> right = deleted;
	} else {
		
		if ((* node) -> left == NULL && (* node) -> right == NULL) {
			freeNode(*node);
			return NULL;
		}

		if ((* node) -> left == NULL || (* node) -> right == NULL) {
			TreeNode * tmp;
			if ((* node) -> left == NULL) {
				tmp = (* node) -> right;
			} else {
				tmp = (* node) -> left;
			}
			freeNode(*node);
			return tmp;
		}

		TreeNode * t = minInSubTree((* node) -> right);
		(* node) -> key = t -> key;	
		(* node) -> right = delete(&((* node) -> right), t -> key);
	} 
	
	return * node;
}

TreeNode * importFromFile(char * filename) {
	FILE * filePtr = fopen(filename, "r");
	if (filePtr == NULL) {
		return NULL;
	}

	TreeNode * root = NULL;

	char * key;

	while (strlen((key = file_readline(filePtr)))) {
		char * value = file_readline(filePtr);
		insert(&root, atoi(key), atoi(value), NULL);
		free(key);
		free(value);
	}

	free(key);

	fclose(filePtr);

	return root;
	
}

int abs(int a) {
	return (a > 0 ? a : -a);
}

void findNearestByKeyRec(TreeNode * node, int key, TreeNode ** last_found, int * dlt) {
	if (node == NULL) {
		return;	
	}
	
	if (* last_found == NULL || ((abs(node -> key - key) < * dlt) && (node -> key != key))) {
		* last_found = node;
		* dlt = abs(key - node -> key);
	}

	findNearestByKeyRec(node -> left, key, last_found, dlt);
	findNearestByKeyRec(node -> right, key, last_found, dlt);
	
}

TreeNode * findNearestByKey(TreeNode * root, int key) {
	TreeNode * node = NULL;
	int dlt = 100000000;
	findNearestByKeyRec(root, key, &node, &dlt);
	return node;
}


TreeNode * search(TreeNode * node, int key) {
	if (node == NULL || node -> key == key) {
		return node;
	}

	return search(key < node -> key ? node -> left : node -> right, key);
}

void freeTree(TreeNode * node) {
	if (node != NULL) {
		freeTree(node -> left);
		freeTree(node -> right);
		freeNode(node);
	}
}


InfoField * searchByKeyAndPos(TreeNode * node, int key, int pos) {

	TreeNode * found = search(node, key);
	if (found == NULL) {
		return NULL;
	}

	int cur = 0;
	InfoField * start = found -> infoNode;

	while (start != NULL && pos != cur) {
		cur++;
		start = start -> next;
	}

	if (pos != cur) {
		return NULL;
	}

	return start;
	
}

void std_print_tree(TreeNode * root, int offset) {

	for (int i = 0; i < offset; i++) {
		printf(" ");
	}

	if (root == NULL) {
		printf("-\n");
	} else {
		printf("%d: ", root -> key);
		InfoField * cur = root -> infoNode;
		while (cur) {
			printf("%d -> ", cur -> value);
			cur = cur -> next;
		}

		printf("NULL\n");
		
		std_print_tree(root -> left, offset + 2);
		std_print_tree(root -> right, offset + 2);
	}
}

void dot_print_null(int key, int nullcount, FILE * out) {
	fprintf(out, "	null%d [shape=point];\n", nullcount);
	fprintf(out, "	%d -> null%d;\n", key, nullcount);
}

void dot_print_node(TreeNode * node, FILE * out, int nullcount) {
	
	if (node -> left != NULL) {
		nullcount += 3;
		fprintf(out, "	%d -> %d;\n", node -> key, node -> left -> key);
		dot_print_node(node -> left, out, nullcount + 397);
		nullcount += 23;
	} else {
		nullcount += 7;
		dot_print_null(node -> key, nullcount + 103, out);
		nullcount += 19;
	}

	if (node -> right != NULL) {
		nullcount += 5;
		fprintf(out, "	%d -> %d;\n", node -> key, node -> right -> key);
		dot_print_node(node -> right, out, nullcount + 101);
		nullcount += 31;
	} else {
		nullcount += 11;
		dot_print_null(node -> key, nullcount + 53, out);
		nullcount += 7;
	}
}

void dot_print_tree(TreeNode * root, char * filename) {
	FILE * out = fopen(filename, "w");
	if (out == NULL) {
		return;
	}

	fprintf(out, "digraph BST {\n");
	fprintf(out, "	node [fontname=\"Mono\"];\n");

	if (root == NULL) {
		fprintf(out, "\n");
	} else if (root -> left == NULL && root -> right == NULL) {
		fprintf(out, "	%d;\n", root -> key);
	} else {
		dot_print_node(root, out, 0);
	}

	fprintf(out, "}\n");

	fclose(out);
}

int digitsCount(int n) {
	int c = 0;
	while (n) {
		 c += 1;
		 n /= 10;
	}
	return c;
}


void specialSearch(TreeNode * node, int digits) {
	if (node == NULL) {
		return;	
	}
	
	if (digitsCount(node -> key) == digits) {
		printf("%d\n", node -> key);
	}

	specialSearch(node -> left, digits);
	specialSearch(node -> right, digits);
}

void exportToFile(TreeNode * root, FILE * file) {
	if (root == NULL) {
		return;
	}
	fprintf(file, "%d: %d\n", root -> key, root -> infoNode -> value);
	exportToFile(root -> left, file);
	exportToFile(root -> right, file);
}

TreeNode * processFile(char * filename, char * output) {
	FILE * file = fopen(filename, "rb");
	if (file == NULL) {
		return NULL;
	}

	FILE * outputFile = fopen(output, "w");
	if (outputFile == NULL) {
		return NULL;
	}

	TreeNode * root = NULL;

	int n;
	fread(&n, sizeof(int), 1, file);

	for (int i = 0; i < n; i++) {
		int num;
		fread(&num, sizeof(int), 1, file);

		InfoField * found = searchByKeyAndPos(root, num, 0);
		if (found == NULL) {
			insert(&root, num, 1, NULL);
		} else {
			insert(&root, num, found -> value + 1, NULL);
		}
		
	}

	exportToFile(root, outputFile);
	
	fclose(outputFile);
	
	fclose(file);

	return root;
}
