#include <stdio.h>

#include <stdlib.h>

#include <string.h>

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

InfoField * createInfoField(int value) {
	InfoField * info = (InfoField *) malloc(sizeof(InfoField) * 1);
	info -> value = value;
	info -> next = NULL;
}

TreeNode * createNode(TreeNode * left, TreeNode * right, TreeNode * prev, int key) {
	TreeNode * node = (TreeNode *) malloc(sizeof(TreeNode) * 1);
	node -> left = left;
	node -> right = right;
	node -> prev = prev;
	node -> key = key;
	node -> infoNode = NULL;
}

void freeNode(TreeNode * node) {

	InfoField * cur = node -> infoNode;
	while (cur) {
		InfoField * tmp = cur -> next;
		free(cur);
		cur = tmp;
		
	}
	
	free(node);

}

TreeNode * minInSubTree(TreeNode * node) {

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
	InfoField * info = createInfoField(value);
	if (* node == NULL) {
		* node = createNode(NULL, NULL, prev, key);
		(* node) -> infoNode = info;
	} else {
		if ( (* node) -> key == key) {
			InfoField * infoNode = (* node) -> infoNode;
			info -> next = infoNode;
			(* node) -> infoNode = info;
		} else {

			if (key < (* node) -> key) {
				insert(&( * node) -> left, key, value, *node);
			} else if (key > (* node) -> key) {
				insert(&( * node) -> right, key, value, *node);
			}
		}
	}
}


TreeNode * delete(TreeNode * * node, int key) {
	if (* node == NULL) {
		return NULL;
	}

	if (key == (* node) -> key) {
		if ( (* node) -> right != NULL && (* node) -> left != NULL) {
			TreeNode * minInRight = minInSubTree( ( * node) -> right);
			(* node) -> key = minInRight -> key;

			if (minInRight -> infoNode == NULL) {
				(* node) -> infoNode = NULL;
			} else {
				InfoField * start = createInfoField(minInRight -> infoNode -> value);
				InfoField * copy = start;
				InfoField * cur = minInRight -> infoNode -> next;
				while (cur) {
					copy -> next = createInfoField(cur -> value);
					cur = cur -> next;
				}

				(* node) -> infoNode = start;
				
			}

			(* node) -> right = delete( &(* node) -> right, (* node) -> key);
			
		} else {
			freeNode(* node);
			if ( (* node) -> right == NULL) {
				(* node) = (* node)->left;
			} else {
				(* node) = (* node) -> right;
			}
		}

	} else if (key < (* node) -> key) {
		TreeNode * left = (* node) -> left;
		(* node) -> key = left -> key;
	
		if (left -> infoNode == NULL) {
			(* node) -> infoNode = NULL;
		} else {
			InfoField * start = createInfoField(left -> infoNode -> value);
			InfoField * copy = start;
			InfoField * cur = left -> infoNode -> next;
			while (cur) {
				copy -> next = createInfoField(cur -> value);
				cur = cur -> next;
			}

			(* node) -> infoNode = start;
			
		}

		(* node) -> left = delete( &(* node) -> left, (* node) -> key);
		
	} else if (key > (* node) -> key) {
		TreeNode * right = (* node) -> right;
		(* node) -> key = right -> key;
	
		if (right -> infoNode == NULL) {
			(* node) -> infoNode = NULL;
		} else {
			InfoField * start = createInfoField(right -> infoNode -> value);
			InfoField * copy = start;
			InfoField * cur = right -> infoNode -> next;
			while (cur) {
				copy -> next = createInfoField(cur -> value);
				cur = cur -> next;
			}

			(* node) -> infoNode = start;
			
		}

		(* node) -> right = delete( &(* node) -> right, (* node) -> key);
		
	}

	return * node;
	
}

TreeNode * search(TreeNode * node, int key) {
	if (node == NULL || node -> key == key) {
		return node;
	}

	return search(key < node -> key ? node -> left : node -> right, key);
}


int main(void) {

	return 0;
}
