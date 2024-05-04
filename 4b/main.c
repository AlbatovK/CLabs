#include <stdio.h>

#include <stdlib.h>

#include "utils.h"

#include "SplayTree.h"

int main(void) {
	SplayTreeNode * tree = NULL;
	int action = 0;
	int k = 0;

	while (action != 4) {
		printf("Enter action. 1 - insert element, 2 - delete element.\n");
		printf("3 - output tree. 4 - exit.\n");

		char * pr = "";
		do {
			printf("%s", pr);
			getInt(&action);
			pr = "No such action. Try again.\n";
		} while (action < 1 || action > 4);

		switch(action) {

			case 1:
			
				printf("Enter key.\n");
				char * key = readline();
				printf("Enter value.\n");
				char * value = readline();
				tree = insertNode(&tree, m_strdup(key));
				printf("Insert key %s with value %s.\n", key, value);
				free(key);
				free(value);
				break;

			case 2:
				printf("Enter key.\n");
				char * keyToDel = readline();
				tree = removeNode(&tree, keyToDel);
				free(keyToDel);
				break;

			case 3:
				printTreeHorizontal(tree);
				char str[1000];
				sprintf(str, "%d", k);
				dotPrintTree(tree, str);
				k += 1;
				break;

			case 4:
				printf("Exiting.\n");
				break;
		}
	}

	freeTree(tree);
	return 0;
}
