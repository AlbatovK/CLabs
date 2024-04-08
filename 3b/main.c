#include <stdio.h>

#include <stdlib.h>

#include "utils.h"

#include "table.h"

int main() {
	Table * table = createTable(TABLE_START_SIZE);
	int action = 0;

	while (action != 8) {

		printf("Enter action. 1 - put key, 2 - delete by key. 3. - import table from binary file.\n");
		printf("4 - export table to binary file, 5 - output tabe, 6 - find all by key.\n");
		printf("7 - find by key and release, 8 - exit program.\n");

		char * pr = "";
		do {
			printf("%s", pr);
			getInt(&action);	
			pr = "No such action. Enter again.\n";
		} while(action < 1 || action > 8);

		switch(action) {

			case 1:
				printf("Enter key:\n");
				char * keyToPut = readline();
				printf("Enter value:\n");
				int value;
				getInt(&value);
				
				int resPut = putKey(&table, keyToPut, value);

				if (resPut == 0) {
					printf("Unable to put key in table. Table is full or equals to null.\n");
					free(keyToPut);
					break;
				}

				printf("Successfully put key with value: %d.\n", value);
				break;
				
			case 2:
				printf("Enter key:\n");
				char * keyToDel = readline();

				int resDel = deleteByKey(table, keyToDel);

				if (resDel == 0) {
					printf("Cannot delete because table is null or key is not present in table.\n");
					free(keyToDel);
					break;
				}

				printf("Successfully deleted key: %s from table.\n", keyToDel);
				free(keyToDel);
				break;
				
			case 3:
				printf("Enter filename:\n");
				char * filename = readline();
				Table * tableFromFile = importFromFile(filename);
				
				if (tableFromFile == NULL) {
					printf("Unable to read table from this file. Try again.\n");
					free(filename);
					break;
				}

				printf("Successfully read table from file.\n");
				freeTable(table);
				free(filename);
				table = tableFromFile;
				break;

			case 4:

				printf("Enter filename:\n");
				char * eName = readline();

				int res = exportToFile(table, eName);

				if (res == 0) {
					printf("Unable to write table to this file. Try again.\n");
					free(eName);
					break;	
				}

				printf("Successfully written to file.\n");
				free(eName);

				break;

			case 5:

				outputTable(table);
				break;

			case 6:
				printf("Enter key:\n");
				char * keyToFind = readline();

				int n = 0;

				KeyEntry * entries = searchByKey(table, keyToFind, &n);

				if (n == 0) {
					printf("Couldn't find any entries.\n");
					free(keyToFind);
					break;
				}

				for (int i = 0; i < n; i++) {
					printf("Entry %d: key - %s, value - %d, release - %d.\n", i + 1, entries[i].key, entries[i].info -> value, entries[i].release);
				}

				free(entries);

				free(keyToFind);
				break;
				
			case 7:

				printf("Enter key:\n");
				char * keyToFindWithRel = readline();

				int releaseToFind;
				printf("Enter release:\n");
				getInt(&releaseToFind);
				
				KeyEntry * found = searchByKeyAndRelease(table, keyToFindWithRel, releaseToFind);

				if (found == NULL) {
					printf("No entris found with key: %s and release: %d.\n", keyToFindWithRel, releaseToFind);
				} else {
					printf("Found entry: key: %s, value: %d, release: %d.\n", keyToFindWithRel, found -> info -> value, releaseToFind);
				}

				free(keyToFindWithRel);
				break;
				
			case 8:
				printf("Exiting.\n");
				break;
		}
	}
	
	freeTable(table);
	return 0;
	
}
