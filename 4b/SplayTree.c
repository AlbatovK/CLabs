#include "SplayTree.h"

#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include "utils.h"

SplayTreeNode * getParentNode(SplayTreeNode * node) {
	if (node == NULL) 
		return NULL;
	return node -> parent;
}

void setNodeParent(SplayTreeNode * child, SplayTreeNode * parent) {
	if (child != NULL)
		child -> parent = parent;
}

void setNodeAsParent(SplayTreeNode * parent) {
	setNodeParent(parent -> left, parent);
	setNodeParent(parent -> right, parent);
}

void rotate(SplayTreeNode * parent, SplayTreeNode * child) {
	SplayTreeNode * grandParent = getParentNode(parent);
	if (grandParent != NULL) {
		if (grandParent -> left == parent) {
			grandParent -> left = child;
		} else {
			grandParent -> right = child;
		}
	}

	if (parent -> left == child) {
		parent -> left = child -> right;
		child -> right = parent;	
	} else {
		parent -> right = child -> left;
		child -> left = parent;
	}

	setNodeAsParent(child);
	setNodeAsParent(parent);
	child -> parent = grandParent;
}

SplayType getSplayType(SplayTreeNode * node) {
	SplayTreeNode * parent = getParentNode(node);
	if (parent == NULL)
		return NONE;
	SplayTreeNode * grandParent = getParentNode(parent);
	if (grandParent == NULL)
		return ZIG;
	if ( (grandParent -> left == parent && parent -> left == node) || (grandParent -> right == parent && parent -> right == node) ) {
		return ZIG_ZIG;
	}

	return ZIG_ZAG;
}


SplayTreeNode * splay(SplayTreeNode * node) {
	SplayType type = getSplayType(node);
	if (type == NONE) {
		return node;
	}

	if (type == ZIG) {
		rotate(getParentNode(node), node);
		return node;
	}

	SplayTreeNode * parent = getParentNode(node);
	SplayTreeNode * grandParent = getParentNode(parent);

	if (type == ZIG_ZIG) {
		rotate(grandParent, parent);
		rotate(parent, node);
	} else if (type == ZIG_ZAG) {
		rotate(parent, node);
		rotate(grandParent,	node);
	}

	return splay(node);
	
}

SplayTreeNode * find(SplayTreeNode * node, KeyType key) {
	if (node == NULL)
		return NULL;

	if (strcmp(key, node -> key) == 0)
		return splay(node);

	if (strcmp(node -> key, key) > 0 && node -> left != NULL)
		return find(node -> left, key);
		
	if (strcmp(node -> key, key) < 0 && node -> right != NULL) 
		return find(node -> right, key);
		
	return splay(node);
}

SplaySplitResult * createSplaySplitResult(SplayTreeNode * left, SplayTreeNode * right, int found) {
	SplaySplitResult * result = (SplaySplitResult * ) malloc(sizeof(SplaySplitResult) * 1);
	result -> left = left;
	result -> right = right;
	result -> found = found;
	return result;
}

SplaySplitResult * split(SplayTreeNode * * root, KeyType key) {
	if (* root == NULL) {
		return createSplaySplitResult(NULL, NULL, 0);
	}	

	(* root) = find(* root, key);
	if ( strcmp( (* root) -> key, key) == 0) {
		setNodeParent( (* root) -> left, NULL);
		setNodeParent( (* root) -> right, NULL);
		return createSplaySplitResult( (* root) -> left, (* root) -> right, 1);
	}

	if ( strcmp( (* root) -> key, key) < 0) {
		SplayTreeNode * right = (* root) -> right;
		(* root) -> right = NULL;
		setNodeParent(right, NULL);
		return createSplaySplitResult( (* root), right, 0);
	} else {
		SplayTreeNode * left = (* root) -> left;
		(* root) -> left = NULL;
		setNodeParent(left, NULL);
		return createSplaySplitResult(left, (* root), 0);
	}
	
}

InfoType * createInfoNode(ValueType	value) {
	InfoType * info = (InfoType *) malloc(sizeof(InfoType) * 1);
	info -> value = value;
	info -> next = NULL;
	return info;
}

SplayTreeNode * createNewNode(KeyType key, SplayTreeNode * left, SplayTreeNode * right) {
	SplayTreeNode * node = (SplayTreeNode *) malloc(sizeof(SplayTreeNode) * 1);
	node -> key = key;
	node -> left = left;
	node -> right = right;
	node -> parent = NULL; 
	node -> infoNode = NULL;
	return node;
}

SplayTreeNode * insertNode(SplayTreeNode * * root, KeyType key) {
	SplaySplitResult * res = split(root, key);
	if (res -> found == 0) {
		* root = createNewNode(key, res -> left, res -> right);
	} else {
		free(key);
	}
	
	setNodeAsParent(* root);
	free(res);
	return * root;
}

SplayTreeNode * merge(SplayTreeNode * * left, SplayTreeNode * * right) {
	if ( (* right) == NULL)
		return (* left);
	if ( (* left) == NULL)
		return (* right);
	(* right) = find( (* right), (* left) -> key);
	(* right) -> left = * left;
	(* left) -> parent = * right;
	return * right;
	
}

void freeNode(SplayTreeNode * node) {
	if (node == NULL)
		return;

	free(node -> key);
	
	free(node);
}

SplayTreeNode * removeNode(SplayTreeNode * * root, KeyType key) {
	SplayTreeNode * found = find(* root, key);
	if (strcmp(found -> key, key) != 0) {
		return * root;
	}
	
	(* root) = found;
	setNodeParent( (* root) -> left, NULL);
	setNodeParent( (* root) -> right, NULL);
	SplayTreeNode * * left = &( (* root) -> left);
	SplayTreeNode * * right = &( (* root) -> right);
	SplayTreeNode * merged = merge(left, right);
	freeNode(found);
	return merged;
}

void printTreeHorizontalRecursive(SplayTreeNode * root, int offset) {

	for (int i = 0; i < offset; i++) {
		printf(" ");
	}

	if (root == NULL) {
		printf("-\n");
	} else {
		printf("%s: ", root -> key);
		InfoType * cur = root -> infoNode;
		while (cur) {
			printf("%s -> ", cur -> value);
			cur = cur -> next;
		}

		printf("NULL\n");
		
		printTreeHorizontalRecursive(root -> left, offset + 2);
		printTreeHorizontalRecursive(root -> right, offset + 2);
	}
}

void printTreeHorizontal(SplayTreeNode * root) {
	printTreeHorizontalRecursive(root, 0);
}

void freeTree(SplayTreeNode * node) {
	if (node == NULL)
		return;

	SplayTreeNode * left = node -> left;
	SplayTreeNode * right = node -> right;

	freeNode(node);
		
	freeTree(left);
	
	freeTree(right);
}

void dotPrintNode(SplayTreeNode * node, FILE * out) {
	if (node -> parent != NULL) {
		fprintf(out, "	%s -> %s;\n", node -> key, node -> parent -> key);
	}
		
	if (node -> left != NULL) {
		fprintf(out, "	%s -> %s;\n", node -> key, node -> left -> key);
		dotPrintNode(node -> left, out);
	}

	if (node -> right != NULL) {
		fprintf(out, "	%s -> %s;\n", node -> key, node -> right -> key);
		dotPrintNode(node -> right, out);
	} 
}

void dotPrintTree(SplayTreeNode * root, char * filename) {
	FILE * out = fopen(filename, "w");
	if (out == NULL) {
		return;
	}

	fprintf(out, "digraph BST {\n");
	fprintf(out, "	node [fontname=\"Mono\"];\n");

	if (root == NULL) {
		fprintf(out, "\n");
	} else if (root -> left == NULL && root -> right == NULL) {
		fprintf(out, "	%s;\n", root -> key);
	} else {
		dotPrintNode(root, out);
	}

	fprintf(out, "}\n");

	fclose(out);
}

SplayTreeNode * findMinNode(SplayTreeNode * root) {
	if (root -> left == NULL)
		return root;
	return findMinNode(root -> left);
}
