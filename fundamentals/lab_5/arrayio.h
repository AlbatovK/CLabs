#ifndef ARRAYIO_H

#define ARRAYIO_H

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>

#include "struct.h"

#include "readline.h"

#include "sort.h"

abonent_t * readArray(int *, int);

void outputArray(abonent_t *, int, int);

void generateRandomInput(int, int);

#endif
