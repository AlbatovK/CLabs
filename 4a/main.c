#include <stdio.h>

#include <stdlib.h>

#include "utils.h"

#include "tree.h"

int main(void) {

	TreeNode * node = processFile("a.txt", "ho.txt");
	dot_print_tree(node, "tree.dot");
	std_print_tree(node, 0);

	freeTree(node);

	return 0;
}
