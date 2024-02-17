#include "readline.h"

char * my_strcat(char * s1, char * s2) {
    int l1 = strlen(s1);
    int l2 = strlen(s2);

    char * s3 = malloc(sizeof(char) * (l1 + l2 + 1));

    memcpy(s3, s1, l1);
    memcpy(s3 + l1, s2, l2 + 1);

    return s3;
}


char * readline(char * msg) {

	printf("%s\n", msg);

	char s[82] = {0};
	char * res = malloc(sizeof(char) * 1);
	res[0] = '\0';
	
	int in = scanf("%81[^\n]", s);
	if (in == 0) {
		scanf("%*c");
		in = scanf("%81[^\n]", s);
	}
	while (in > 0) {

		char * tmp = res;
		res = my_strcat(s, res);
		free(tmp);

		in = scanf("%81[^\n]", s);
	}
	
	return res;
}


char * file_readline(FILE * file_ptr) {
	char s[81] = {0};
	char * res = malloc(sizeof(char) * 1);
	res[0] = '\0';
	
	int in = fscanf(file_ptr, "%81[^\n]", s);
	if (in == 0) {
		fscanf(file_ptr, "%*c");
		in = fscanf(file_ptr, "%81[^\n]", s);
	}
	while (in > 0) {

		char * tmp = res;
		res = my_strcat(s, res);
		free(tmp);

		in = fscanf(file_ptr, "%81[^\n]", s);
	}
	
	return res;
}
