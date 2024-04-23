#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include "utils.h"

#include "tree.h"

void profile() {
	FILE * file = fopen("profiling.txt", "w");
	TreeNode * tree = NULL;
	srand(time(NULL));

	int testCount = 20;

	int ns[] = {10, 50, 100, 150, 200, 300, 500, 700, 1000, 2000, 3000,  5000, 10000};
	for (unsigned int j = 0; j < sizeof(ns) / sizeof(int); j++) {
		int n = ns[j];
		int sm1 = 0;
		for (int k = 0; k < testCount; k++) {
			int start = clock();
			for (int i = 0; i < n; i++) {
				insert(&tree, rand() % 100, 0, NULL);
			}
			int end = clock();
			sm1 += end - start;
			freeTree(tree);
			tree = NULL;
		}
		sm1 /= testCount;
		printf("%d - %d\n", n, sm1);

		int sm2 = 0;
		for (int k = 0; k < testCount; k++) {
			int start = clock();
			for (int i = 0; i < n; i++) {
				search(tree, rand() % 1000);
			}
			int end = clock();
			sm2 += end - start;
			freeTree(tree);
			tree = NULL;
		}
		sm2 /= testCount;
		printf("%d - %d\n", n, sm2);

		int sm3 = 0;
		for (int k = 0; k < testCount; k++) {
			int start = clock();
			for (int i = 0; i < n; i++) {
				tree = delete(&tree, rand() % 1000);
			}
			int end = clock();
			sm3 += end - start;
			freeTree(tree);
			tree = NULL;
		}
		sm3 /= testCount;
		printf("%d - %d\n", n, sm3);

		fprintf(file, "%d;%d;%d;%d\n", n, sm1, sm2, sm3);
	
	}

	fclose(file);
	
}

void makeTestBin() {
	FILE * file = fopen("test.bin", "wb");
	int n = 10;
	fwrite(&n, sizeof(int), 1, file);
	for (int i = 0; i < n; i++) {
		int num = rand() % 100;
		fwrite(&num, sizeof(int), 1, file);
	}
	fclose(file);
}

int main(void) {
	makeTestBin();
	TreeNode * tree = NULL;
	int action = 0;

	while (action != 11) {
		printf("Enter action. 1 - insert element, 2 - delete element, 3 - search by digits count.\n");
		printf("4 - search by key and position, 5 - import from text file, 6 - additional task.\n");
		printf("7 - output like a tree, 8 - standard horizontal output, 9 - output to dot.\n");
		printf("10 - find nearest by key, 11 - exit, 12 - profile.\n");


		char * pr = "";
		do {
			printf("%s", pr);
			getInt(&action);
			pr = "No such action. Try again.\n";
		} while (action < 1 || action > 12);

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
				int keyNearest;
				printf("Enter key to find nearest.\n");
				getInt(&keyNearest);
				TreeNode * node = findNearestByKey(tree, keyNearest);
				if (node == NULL) {
					printf("Tree is empty or invalid. No elements found.\n");
					break;
				}
				printf("Found element with key: %d\n", node -> key);
				break;

			case 11:
				printf("Exiting.\n");
				break;	

			case 12:
				printf("Profiling...\n");
				profile();
				printf("Done!\n");
				break;
		}
	}

	freeTree(tree);
	return 0;
}
