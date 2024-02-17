#include "sort.h"

// void swap(abonent_t * obj1, abonent_t * obj2) {
// 	char * name = obj1 -> name;
// 	obj1 -> name = obj2 -> name;
// 	obj2 -> name = name;
// 
// 	char * phoneNumber = obj1 -> phoneNumber;
// 	obj1 -> phoneNumber = obj2 -> phoneNumber;
// 	obj2 -> phoneNumber = phoneNumber;
// 
// 	int tmp = obj1 -> timestamp;
// 	obj1 -> timestamp = obj2 -> timestamp;
// 	obj2 -> timestamp = tmp;
// }

void swap(abonent_t * obj1, abonent_t * obj2) {
	abonent_t * tmp = malloc(sizeof(abonent_t) * 1);
	memcpy(tmp, obj1, sizeof(abonent_t));
	memcpy(obj1, obj2, sizeof(abonent_t));
	memcpy(obj2, tmp, sizeof(abonent_t));
	free(tmp);
}

int compareAbonentByName(abonent_t obj1, abonent_t obj2) {
	return strcmp(obj1.name, obj2.name) > 0 ? 1 : 0;
}

int compareAbonentByPhoneNumber(abonent_t obj1, abonent_t obj2) {
	return strcmp(obj1.phoneNumber, obj2.phoneNumber) > 0 ? 1 : 0;
}

int compareAbonentByTimestamp(abonent_t obj1, abonent_t obj2) {
	return obj1.timestamp > obj2.timestamp ? 1 : 0;
}

int compareAbonent(abonent_t obj1, abonent_t obj2, int field) {
	switch (field) {
		case 0:
			return compareAbonentByName(obj1, obj2);
		case 1:
			return compareAbonentByPhoneNumber(obj1, obj2);
		case 2:
			return compareAbonentByTimestamp(obj1, obj2);
	}
}


void sortDoubleSelection(abonent_t * arr, int n, int field, int direction) {

	for (int i = 0; i < n / 2; i++) {

		int min_i = i, max_i = i;
		abonent_t min = arr[i], max = arr[i];

		for (int j = i + 1; j < n - i; j++) {
			if (compareAbonent(arr[j], max, field) == direction) {
				max = arr[j];
				max_i = j;
			} 
			if (compareAbonent(min, arr[j], field) == direction) {
				min = arr[j];
				min_i = j;
			}
		}

		if (i == max_i) {
			max_i = min_i;
		}

		swap(&arr[i], &arr[min_i]);
		swap(&arr[n - i - 1], &arr[max_i]);
		
	}
}

void sortOddEven(abonent_t * arr, int n, int field, int direction) {
	int sorted = 0;
	while (!sorted) {	
		sorted = 1;
		for (int i = 1; i < n - 2; i += 2) {
			if (compareAbonent(arr[i], arr[i + 1], field) == direction) {
				swap(&arr[i], &arr[i + 1]);
				sorted = 0;
			}
		}
		
		for (int i = 0; i < n - 2; i += 2) {
			if (compareAbonent(arr[i], arr[i + 1], field) == direction) {
				swap(&arr[i], &arr[i + 1]);
				sorted = 0;
			}
		}
	}
}

int compareAbonentByNameVoidAscending(const void * obj1, const void * obj2) {
	abonent_t * a = (abonent_t *) obj1;
	abonent_t * b = (abonent_t *) obj2;
	return strcmp(a -> name, b -> name) > 0 ? 1 : 0;
}

int compareAbonentByPhoneNumberVoidAscending(const void * obj1, const void * obj2) {
	abonent_t * a = (abonent_t *) obj1;
	abonent_t * b = (abonent_t *) obj2;
	return strcmp(a -> phoneNumber, b -> phoneNumber) > 0 ? 1 : 0;
}

int compareAbonentByTimestampVoidAscending(const void * obj1, const void * obj2) {
	abonent_t * a = (abonent_t *) obj1;
	abonent_t * b = (abonent_t *) obj2;
	return a -> timestamp > b -> timestamp ? 1 : 0;
}

int compareAbonentByNameVoidDescending(const void * obj1, const void * obj2) {
	abonent_t * a = (abonent_t *) obj1;
	abonent_t * b = (abonent_t *) obj2;
	return strcmp(a -> name, b -> name) > 0 ? 0 : 1;
}

int compareAbonentByPhoneNumberVoidDescending(const void * obj1, const void * obj2) {
	abonent_t * a = (abonent_t *) obj1;
	abonent_t * b = (abonent_t *) obj2;
	return strcmp(a -> phoneNumber, b -> phoneNumber) > 0 ? 0 : 1;
}

int compareAbonentByTimestampVoidDescending(const void * obj1, const void * obj2) {
	abonent_t * a = (abonent_t *) obj1;
	abonent_t * b = (abonent_t *) obj2;
	return a -> timestamp > b -> timestamp ? 0 : 1;
}

void sortQuickSort(abonent_t * arr, int n, int field, int direction) {
	switch(field) {
		case 0:
			qsort(arr, n, sizeof(abonent_t), direction ? compareAbonentByNameVoidAscending : compareAbonentByNameVoidDescending);
		case 1:
			qsort(arr, n, sizeof(abonent_t), direction ? compareAbonentByPhoneNumberVoidAscending : compareAbonentByPhoneNumberVoidDescending);
		case 2:
			qsort(arr, n, sizeof(abonent_t), direction ? compareAbonentByTimestampVoidAscending : compareAbonentByTimestampVoidDescending);
	}
}

void freeAbonentArr(abonent_t * arr, int n) {

	for (int i = 0; i < n; i++) {
		abonent_t abonent = arr[i];
		free(abonent.name);
		free(abonent.phoneNumber);
	}
	
	free(arr);
	
}
