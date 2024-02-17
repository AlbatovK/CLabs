#include <stdio.h>

#include <stdlib.h>

#include "array.h"

#include "interface.h"

void enterCommand(int * mode) {
  printf("Enter Command.\n");
  while(scanf("%d", mode) !=1 || *mode < 0 || *mode > 6) {
    clearBuffer();
    printf("Invalid command. Enter again.\n");
  }
}

int menu() {
  printf("1 - Initialize array. 2 - Print array contents. 3 - Insert new element.\n");
  printf("4 - Delete an element. 5 - Form new sequance. 6 - exit the program.\n");

  int mode = 0;
  int * arr;
  int initialized = 0;
  int n = 0;

  while(1) {
    enterCommand(&mode);
    switch(mode) {

      case 1:
        int n;
        printf("Enter array length.\n");
       
        while(scanf("%d", &n) != 1 || n < 1) {
          clearBuffer();
          printf("Incorrect array length. Enter again.\n");
        }
        if (initialized) {
	  free(arr);	
	}
        arr = initializeArray(n);
        printArray(arr, n);
        printf("Initialized array with length %d.\n", n);
        initialized = 1;
        break;

      case 2:
        if (!initialized) {
          printf("You must initialize array.\n");
          break;
        }
        printArray(arr, n);
        printf("Printed array with length %d.\n", n);
        break;

      case 3:
        if (!initialized) {
          printf("You must initialize array.\n");
          break;
        }

        int x, i;
        printf("Enter element and index to insert.\n");
        while (scanf("%d %d", &x, &i) != 2 || i < 0) {
          clearBuffer();
          printf("Invalid input. Enter again.\n");
        }
        
        arr = insertElement(arr, &n, x, i);
        printArray(arr, n);
        break;

      case 4:
        if (!initialized) {
          printf("You must initialize array.\n");
          break;
        }
        int index;
        printf("Enter index of element to delete.\n");
        while (scanf("%d", &index) != 1 || index < 0 || index > n) {
          clearBuffer();
          printf("Invalid input. Enter again.\n");
        }
        
        arr = deleteElement(arr, &n, index);
        printArray(arr, n);
        break;

      case 5:
        if (!initialized) {
          printf("You must initialize array.\n");
          break;
        }

        int k = n;
        arr = formB(arr, &n);
		    printArray(arr, n);
		    printf("Deleted %d elements.\n", k - n);
        break;        
        
      case 6:
         printf("Exiting the program.\n");
         if (n != 0) {
          free(arr);
         }
         return 0;
    }
  }
}

int main() {
  menu();
  return 0;
}
