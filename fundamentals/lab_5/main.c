#include <stdio.h>

#include <time.h>

#include <stdlib.h>

#include <string.h>

#include "struct.h"

#include "arrayio.h"

#include "sort.h"

int main() {

	srand(time(NULL));

	abonent_t * arr;
	int len = 0;
	int initialized = 0;

	int action = 0;
	int mode = -1;

	int srtName = 0;
	int srtNum = 0;
	int srtTime = 0;

	
	while (action != 4) {

		printf("Enter action. 1 - read array, 2 - write array, 3 - sort array, 4 - exit the program.\n");
		while (scanf("%d", &action) != 1 || action < 1 || action > 4) {
			while (getchar() != '\n') {}
			fflush(stdin);
			printf("Enter valid command.\n");
		}

		switch(action) {

			case 1:
	
				if (initialized) {
					freeAbonentArr(arr, len);
					len = 0;
				}
				
				mode = -1;
				printf("Enter mode. 0 - read from standart input. 1 - read from txt file. 2 - read from binary file. 3 - generate random value array.\n");
				while (scanf("%d", &mode) != 1 || mode < 0 || mode > 3) {
					while (getchar() != '\n') {}
					fflush(stdin);
					printf("Enter valid mode.\n");
				}

				arr = readArray(&len, mode);
				if (arr == NULL) {
 					printf("Unable to read array. Enter valid data and try again.\n");
 					continue;
 				}
 				
				printf("Initialized an array with length %d.\n", len);
				initialized = 1;
				break;

			case 2:

				if (!initialized) {
					printf("Array is not initialized. Initialize the array first.\n");
					continue;
				}

				mode = -1;
				printf("Enter mode. 0 - write to standart output. 1 - write to txt file. 2 - write to binary file.\n");
				while (scanf("%d", &mode) != 1 || mode < 0 || mode > 2) {
					while (getchar() != '\n') {}
					fflush(stdin);
					printf("Enter valid mode.\n");
				}
				
				outputArray(arr, len, mode);
				printf("Wrote an array with length %d.\n", len);
				break;

			case 3:

				if (!initialized) {
					printf("Array is not initialized. Initialize the array first.\n");
					continue;
				}

				int sort_algol = -1;
				printf("Choose sorting algorithm. 1 - Quick Sort. 2 - Odd Event sort. 3 - Double Selection sort.\n");
				while (scanf("%d", &sort_algol) != 1 || sort_algol < 1 || sort_algol > 3) {
					while (getchar() != '\n') {}
					fflush(stdin);
					printf("Enter valid algorithm.\n");
				}

				int field = -1;
				printf("Enter field to sort by. 0 - by name, 1 - by phone number, 2 - by last phone call time.\n");
				while (scanf("%d", &field) != 1 || field < 0 || field > 2) {
					while (getchar() != '\n') {}
					fflush(stdin);
					printf("Enter valid field.\n");
				}

				int order = -1;
				printf("Enter field to sort by. 0 - descending order, 1 - ascending order.\n");
				while (scanf("%d", &order) != 1 || order < 0 || order > 3) {
					while (getchar() != '\n') {}
					fflush(stdin);
					printf("Enter valid order.\n");
				}

				clock_t begin = clock();
				
				switch (sort_algol) {
					case 1:
						sortQuickSort(arr, len, field, order);
						break;
					case 2:
						sortOddEven(arr, len, field, order);
						break;
					case 3:
						sortDoubleSelection(arr, len, field, order);
						break;
				}

				clock_t end = clock();
				printf("Sorted array with length %d by %lf seconds.\n", len, (double) (end - begin) / CLOCKS_PER_SEC);
				break;
			
			case 4:
			
				if (!initialized) {
					printf("Array is not initialized. Initialize the array first.\n");
					continue;
				}
				
				freeAbonentArr(arr, len);
				return 0;		
		}
	}
}
