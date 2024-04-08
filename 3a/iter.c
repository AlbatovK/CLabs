#include "iter.h"

#include <stdlib.h>

Iter * begin(Table * table) {
	Iter * iter = (Iter *) malloc(sizeof(Iter));
	iter -> table = table;
	iter -> current = table -> keySpace -> entries;
	return iter;
}

Iter * end(Table * table) {
	Iter * iter = (Iter *) malloc(sizeof(Iter));
	iter -> table = table;
	iter -> current = table -> keySpace -> entries + table -> ksSize - 1;
	return iter;
}

void freeIter(Iter * iter) {
	free(iter);
}

int compare(Iter * o1, Iter * o2) {
	return o1 -> current == o2 -> current;
}

int hasNext(Iter * iter) {
	return iter -> current != iter -> table -> keySpace -> entries + iter -> table -> ksSize;
}

void next(Iter * iter) {
	iter -> current ++;
}

