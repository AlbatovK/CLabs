#include <stdio.h>

#include <stdlib.h>

#include "table.h"

#include "utils.h"

int main() {

	Table * table = createTable(TABLE_SIZE);

	outputTable(table);

	for (int i = 0; i < 4; i++) {
		char * s = readline();

		int n;

		getInt(&n);
		
		putKey(table, s, n);
	
		outputTable(table);
	}

	char * s = readline();

	int n;
	KeyEntry * res = searchByKey(table, s, &n);

	for (int i = 0; i < n; i++) {
		printf("%d ", res[i].info -> value);
	}

	free(s);

	printf("\n");

	free(res);
	
	freeTable(table);

	return 0;
}
