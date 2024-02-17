#include "array.h"

int * deleteElement(int * arr, int * n, int index) {
  if (* n == 0  || index >= *n || index < 0) {
    return arr;
  }
  int k = 0;
  for (int * i = arr; i < arr + *n; i++) {
  	if (i - arr == index) {
  	  continue;
  	}
  	arr[k] = *i;
  	k++;
  }
  *n -= 1;
  return realloc(arr, (*n) * sizeof(int));
}

int * insertElement(int * arr, int * n, int x, int i) {
  if (i < 0) {
    return arr;
  }
  int * new_array = realloc(arr, (*n + 1) * sizeof(int));
  if (i > *n) {
  	i = *n;
  }
  for (int j = *n; j > i; j--) {
    new_array[j] = new_array[j - 1];
  }
  new_array[i] = x;
  *n += 1;
  return new_array;
}

int * formB(int * arr, int * n) {
  int k;
  for (k = -1; 3 * (k + 1) + 2 < *n; k++) {}
  if (k == -1) {
  	return arr;
  }
  int * b_arr = malloc((k + 1) * sizeof(int));
  for (int i = 0; i <= k; i++) {
  	b_arr[i] = arr[3 * i] + arr[3 * i + 1] + arr[3 * i + 2];
  }
  int i = 0;
  while (i != *n) {
  	for (int j = 0; j <= k; j++) {
  		if (b_arr[j] == arr[i]) {
  		  arr = deleteElement(arr, n, i);
  		  i--;
  		  break;
  		}
  	}
  	i++;
  }
  free(b_arr);
  return arr;
}
