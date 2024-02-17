#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include "list.h"

#include "ind_task.h"

int main() {

	int action = 0;
	int initialized = 0;
	list_t * list = NULL;

	while (action != 4) {
		printf("Enter action. 1 - read list, 2 - output list, 3 - delete words with even count of vowels, 4 - exit the program.\n");
		while (scanf("%d", &action) != 1 || action < 1 || action > 4) {
			while (getchar() != '\n') {}
			fflush(stdin);
			printf("Enter valid command.\n");
		}

		switch(action) {

			case 1:
				if (initialized) {
					freeList(list);
				}

				printf("Input list:\n");
				list = inputList();

				if (list == NULL) {
					printf("Error. Enter non-empty list.\n");
					continue;
				}

				initialized = 1;
				break;
			
			case 2:

				if (!initialized) {
					printf("List is not initialized.\n");
					continue;
				}

				outputList(list);
				break;

			case 3:

				if (!initialized) {
					printf("List is not initialized.\n");
					continue;
				}

				deleteAllWordsWithEvenVowels(list);
				printf("Deleted words with even count of vowels.\n");
				outputList(list);
				break;

			case 4:
				if (initialized) {
					freeList(list);
				}
				
				return 0;
		}
	}
}
