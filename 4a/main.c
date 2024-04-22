#include <stdio.h>

#include <stdlib.h>

#include "utils.h"

#include "tree.h"

int main(void) {
	TreeNode * tree = NULL;
	int action = 0;

	while (action != 10) {
		printf("Enter action. 1 - insert element, 2 - delete element, 3 - search by digits count.\n");
		printf("4 - search by key and position, 5 - import from text file, 6 - additional task.\n");
		printf("7 - output like a \"tree\", 8 - standard horizontal output, 9 - output to dot, 10 - exit.\n");


		char * pr = "";
		do {
			printf("%s", pr);
			getInt(&action);
			pr = "No such action. Try again.\n";
		} while (action < 1 || action > 10);

		switch(action) {

			case 1:
				printf("Enter key.\n");
				int key;
				getInt(&key);
				printf("Enter value.\n");
				int value;
				getInt(&value);
				insert(&tree, key, value, NULL);
				printf("Insert key %d with value %d.\n", key, value);
				break;

			case 4:
				int keyToSearch;
				printf("Enter key.\n");
				getInt(&keyToSearch);
				int position;
				printf("Enter element position.\n");
				getInt(&position);
				InfoField * field = searchByKeyAndPos(tree, keyToSearch, position);
				if (field == NULL) {
					printf("No such element with position %d and key %d.\n", keyToSearch, position);
					break;
				}

				printf("Found element with value %d.\n", field -> value);
				break;

			case 6:
				freeTree(tree);
				printf("Enter input text file name.\n");
				char * addIFile = readline();
				printf("Enter output tree data name.\n");
				char * outIFile = readline();
				tree = processFile(addIFile, outIFile);
				if (tree == NULL) {
					printf("Error processing data: file may not exist or be empty.\n");
				} else {
					printf("Successfully processed data and exported to %s.\n", outIFile);
				}
				
				free(addIFile);
				free(outIFile);
				break;

			case 7:
				printBinaryTree(tree);
				break;

			case 2:
				printf("Enter key.\n");
				int keyToDelete;
				getInt(&keyToDelete);
				tree = delete(&tree, keyToDelete);
				printf("Deleted element with key %d.\n", keyToDelete);
				break;

			case 3:
				printf("Enter key digits count.\n");
				int digitsCount = 0;
				getInt(&digitsCount);
				specialSearch(tree, digitsCount);
				break;

			case 5:
				printf("Enter filename to import from.\n");
				char * iFile = readline();
				freeTree(tree);

				tree = importFromFile(iFile);
				
				free(iFile);
				break;

			case 8:
				std_print_tree(tree, 0);
				break;

			case 9:
				printf("Enter filename to export (.dot).\n");
				char * eFile = readline(); 
				dot_print_tree(tree, eFile);
				printf("Exported to %s.\n", eFile);
				free(eFile);
				break;
			
			case 10:
				printf("Exiting.\n");
				break;	
		}
	}

	freeTree(tree);
	return 0;
}
