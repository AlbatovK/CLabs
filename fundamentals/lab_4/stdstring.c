#include "stdstring.h"

char * process_str(char ** str) {
	char * s = *str;
	
    char * processed = malloc(sizeof(char) * 1);
    * processed = '\0';
	char * token = strtok(s, "\t ");
	while (token != NULL) {
       char * tmp = processed;
       if (strlen(processed)) {
      	 char * res = my_strcat(" ", token);
	  	 processed = my_strcat(processed, res);
	  	 free(res);
	   } else {
	     processed = my_strcat(processed, token);
	   }
	   free(tmp);
	   token = strtok(NULL, "\t ");
	}
	
	return processed;
}

int solve(char ** str) {
    int summ = 0;
    char op = '+';

    char * token = strtok(*str, "\t ");
    while (token != NULL) {
        if (strlen(token) == 1 && (token[0] == '+' || token[0] == '-')) {
            op = token[0];
        } else {
            int num = my_atoi(token);
            summ += (op == '+' ? num : -num);
        }
        token = strtok(NULL, "\t ");
    }   

    return summ;
}

char * id(char ** s) {
    char * tmp = malloc(sizeof(char) * (strlen(*s) + 1));
    memcpy(tmp, *s, strlen(*s) + 1);

    int n = solve(s);
    char * n_s = my_itoa(n);
    char * res_s = my_strcat(" = ", n_s);
    char * res = my_strcat(tmp, res_s);

    free(n_s);
    free(res_s);
    free(tmp);

    return res;
}
