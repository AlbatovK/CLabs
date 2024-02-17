#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include "mystring.h"

#include "stdstring.h"


void my_menu() {

	char * s = my_readline("");
	
	while (s != NULL && my_strlen(s) != 0) {
		clock_t begin = clock();

        char * res = my_process_str(&s);
		char * equasion = my_id(&res);
		printf("%s\n", equasion);   
		
		free(equasion);
        free(res);
		free(s);
		
        clock_t end = clock();
        printf("Time for execution: %.16lf\n", (double) (end - begin) / CLOCKS_PER_SEC);
    	s = my_readline("");
    }

   	free(s);
   	
}

void menu() {
	char * s = my_readline("");
	
	while (s != NULL && strlen(s) != 0) {
   		clock_t begin = clock();

        char * res = process_str(&s);
		char * equasion = id(&res);
		printf("%s\n", equasion);   
		
		free(equasion);
        free(res);
		free(s);
		
        clock_t end = clock();
        printf("Time for execution: %.16lf\n", (double) (end - begin) / CLOCKS_PER_SEC);
    	s = my_readline("");
    }

   	free(s);
   	
}

int main() {
	int mode;
	printf("Enter mode: 0 for my own string functions, 1 for standard string.h functions.\n");
	while (scanf("%d", &mode) != 1 || (mode != 1 && mode != 0)) {
		while (getchar() != '\n') {} 
		fflush(stdin);
		printf("Invalud input. Enter 0 or 1.\n");
	}

	if (mode == 1) {
		printf("Executing standard functions from string.h\n");
		menu();
	} else {
		printf("Executing my own string functions.\n");
		my_menu();
	}
	
	return 0;
}
