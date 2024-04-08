#ifndef ITER_H

#define ITER_H

#include "table.h"

typedef struct Iter {
	Table * table;
	KeyEntry * current;
} Iter;

Iter * begin(Table * table);

Iter * end(Table * table);

int compare(Iter * o1, Iter * o2);

void next(Iter * iter);

int hasNext(Iter * iter);

void freeIter(Iter * iter);

#endif
