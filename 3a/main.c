#include <stdio.h>

#include <stdlib.h>

#include "utils.h"

#include "table.h"

int main() {
	Table * table = createTable(TABLE_SIZE);
	int action = 0;

	while (action != 8) {

		printf("Enter action. 1 - put key, 2 - delete by key, 3 - delete by key and release.\n");
		printf("4 - import table from csv file, 5 - output table, 6 - find by key, 7 - find by key and release.\n");
		printf("8 - exit program.\n");

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
				char * value = readline();
				
				int resPut = putKey(table, keyToPut, value);

				if (resPut == 0) {
					printf("Unable to put key in table. Table is full or equals to null.\n");
					free(keyToPut);
					free(value);
					break;
				}

				printf("Successfully put key with value: %s.\n", value);
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

				printf("Enter key:\n");
				char * keyToDelWithRel = readline();

				int release;
				printf("Enter release:\n");
				getInt(&release);
				
				int resDelWithRel = deleteByKeyAndRelease(table, keyToDelWithRel, release);

				if (resDelWithRel == 0) {
					printf("Cannot delete because table is null, key is not present in table or it has no such release.\n");
					free(keyToDelWithRel);
					break;
				}

				printf("Successfully deleted key: %s from table.\n", keyToDelWithRel);
				free(keyToDelWithRel);
				break;
			
				
			case 4:
				printf("Enter filename:\n");
				char * filename = readline();
				Table * tableFromFile = importFromFile(filename);
				
				if (tableFromFile == NULL) {
					printf("Unable to read table from this file. Try again.\n");
					freeTable(tableFromFile);
					free(filename);
					break;
				}
				
				freeTable(table);
				free(filename);
				table = tableFromFile;
				break;

			case 5:

				outputTable(table);
				break;

			case 6:
				printf("Enter key:\n");
				char * keyToFind = readline();

				Table * foundTable = findByKey(table, keyToFind);

				printf("Result Table:\n");
				outputTable(foundTable);

				freeTable(foundTable);

				free(keyToFind);
				break;
				
			case 7:

				printf("Enter key:\n");
				char * keyToFindWithRel = readline();

				int releaseToFind;
				printf("Enter release:\n");
				getInt(&releaseToFind);
				
				InfoType * found = findByKeyAndRelease(table, keyToFindWithRel, releaseToFind);

				if (found == NULL) {
					printf("No entris found with key: %s and release: %d.\n", keyToFindWithRel, releaseToFind);
				} else {
					printf("Found entry: key: %s, value: %s, release: %d.\n", keyToFindWithRel, * found, releaseToFind);
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
