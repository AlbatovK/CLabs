#include "interface.h"

void clearBuffer() {
	while (getchar() != '\n') {}
	fflush(stdin);
}


int * initializeArray(int n) {
  int * arr = malloc(sizeof(int) * n);
  for (int * i = arr; i < arr + n; i++) {
    while(scanf("%d", i) != 1) {
      clearBuffer();
      printf("Invalid input. Enter again.\n");
    }
  }
  return arr;
}


void printArray(int * arr, int n) {
  for (int * i = arr; i < arr + n; i++) {
    printf("%d ", *i);
  }
  printf("\n");
}