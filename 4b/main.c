#include <stdio.h>

#include <stdlib.h>

#include "utils.h"

#include "SplayTree.h"

int main(void) {
	SplayTreeNode * tree = NULL;
	int action = 0;
	int k = 0;

	while (action != 8) {
		printf("Enter action. 1 - insert element, 2 - delete element.\n");
		
		printf("3 - output tree. 4 - find by key. 5 - find minimum node.\n");

		printf("6 - import tree from file, 7 - post order traversal, 8 - exit.\n");

		char * pr = "";
		do {
			printf("%s", pr);
			
			getInt(&action);
			
			pr = "No such action. Try again.\n";
			
		} while (action < 1 || action > 8);

		switch(action) {

			case 1:
				printf("Enter key.\n");
				char * key = readline();
				printf("Enter value.\n");
				char * value = readline();
				tree = insertNode(&tree, m_strdup(key), m_strdup(value));
				printf("Insert key %s with value %s.\n", key, value);
				free(key);
				free(value);
				break;

			case 2:
				printf("Enter key.\n");
				char * keyToDel = readline();
				tree = removeNode(&tree, keyToDel);
				printf("Deleted element with key %s.\n", keyToDel);
				free(keyToDel);
				break;

			case 3:
				printTreeHorizontal(tree);
				char filename[1000];
				sprintf(filename, "%d.dot", k);
				dotPrintTree(tree, filename);
				printf("Saved tree to %s.\n", filename);
				k += 1;
				break;

			case 4:
				printf("Enter key.\n");
				char * keyToFind = readline();
				InfoType * info = findByKey(&tree, keyToFind);
				if (info == NULL) {
					printf("Couldn't find node with key: %s.\n", keyToFind);
				} else {
					while (info) {
						printf("%s -> ", info -> value);
						info = info -> next;
					}
					printf("NULL\n");
				}

				free(keyToFind);
				break;

			case 5:
				SplayTreeNode * min = findMinNode(tree);
				if (min == NULL) {
					printf("Tree is empty.\n");
				} else {
					printf("Found node with key: %s.\n", min -> key);
					InfoType * mInfo = min -> infoNode;
					while (mInfo) {
						printf("%s -> ", mInfo -> value);
						mInfo = mInfo -> next;
					}
					printf("NULL\n");
				}

				break;

			case 6:
				printf("Enter filename to import from.\n");

				char * iFile = readline();

				SplayTreeNode * root = importTreeFromFile(iFile);
				if (root == NULL) {
					printf("Couldn't import tree from file.\n");
				} else {
					freeTree(tree);
					tree = root;
				}

				free(iFile);
				break;
				
			case 7:
				postOrderTraversal(tree);
				break;
			
			case 8:
				printf("Exiting.\n");
				freeTree(tree);
				break;
		}
	}

	return 0;
}
