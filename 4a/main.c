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


int maxDepth(TreeNode * node) {
	if (node == NULL) {
		return 0;
	}

	int rightDepth = maxDepth(node -> right);
	int leftDepth = maxDepth(node -> left);
	
	return 1 + (rightDepth > leftDepth ? rightDepth : leftDepth); 
}

typedef struct TreeNodeMeta {
	TreeNode * node;
	int curLevel;
} TreeNodeMeta;

void dot_print_null(int key, int nullcount, FILE * out) {
	fprintf(out, "	null%d [shape=point];\n", nullcount);
	fprintf(out, "	%d -> null%d;\n", key, nullcount);
}

void dot_print_node(TreeNode * node, FILE * out, int nullcount) {
	nullcount++;
	if (node -> left != NULL) {
		nullcount += 7;
		fprintf(out, "	%d -> %d;\n", node -> key, node -> left -> key);
		dot_print_node(node -> left, out, nullcount + 1);
		nullcount++;
	} else {
		nullcount += 3;
		dot_print_null(node -> key, nullcount + 1, out);
		nullcount++;
	}

	if (node -> right != NULL) {
		nullcount += 11;
		fprintf(out, "	%d -> %d;\n", node -> key, node -> right -> key);
		dot_print_node(node -> right, out, nullcount + 1);
		nullcount++;
	} else {
		nullcount += 13;
		dot_print_null(node -> key, nullcount + 1, out);
		nullcount++;
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

void std_print_tree(TreeNode * root, int offset) {

	for (int i = 0; i < offset; i++) {
		printf(" ");
	}

	if (root == NULL) {
		printf("-\n");
	} else {
		printf("%d\n", root -> key);
		std_print_tree(root -> left, offset + 2);
		std_print_tree(root -> right, offset + 2);
	}
}




int main(void) {

	TreeNode * node = NULL;
	std_print_tree(node, 0);
	dot_print_tree(node, "tree1.dot");
	insert(&node, -1, 20, NULL);
	std_print_tree(node, 0);
	dot_print_tree(node, "tree2.dot");
	insert(&node, 3, 20, NULL);
	std_print_tree(node, 0);
	dot_print_tree(node, "tree3.dot");
	insert(&node, -2, 5, NULL);
	std_print_tree(node, 0);
	dot_print_tree(node, "tree4.dot");
	insert(&node, 65, 5, NULL);
	std_print_tree(node, 0);
	dot_print_tree(node, "tree5.dot");
	insert(&node, 4, 5, NULL);
	std_print_tree(node, 0);
	dot_print_tree(node, "tree6.dot");
	insert(&node, -23, 5, NULL);
	std_print_tree(node, 0);
	dot_print_tree(node, "tree7.dot");
	insert(&node, 23, 5, NULL);
	std_print_tree(node, 0);
	dot_print_tree(node, "tree8.dot");
	delete(&node, -1);

	std_print_tree(node, 0);
	dot_print_tree(node, "tree9.dot");

	return 0;
}
