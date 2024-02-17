#include "mystring.h"

int my_atoi(char * s) {
    int sign = 1;
    if (s[0] == '-') {
        sign = -1;
        s++;
    }

    int num = 0;
    for (char * i = s; *i != '\0'; i++) {
        num *= 10;
        num += *i - '0';
    }

    return sign * num;
}

int reverse(int n) {
	int res = 0;
	while (n) {
		res *= 10;
		res += n % 10;
		n /= 10;
	}
	return res;
}

int num_len(int n) {
    int len = 0;
    while (n) {
        n /= 10;
        len += 1;
    }
    return len;
}

char * my_itoa(int n) {

	if (n == 0) {
		char * s = malloc(sizeof(char) * 2);
		s[0] = '0';
		s[1] = '\0';
		return s;
	}

    int sign = 0;
    if (n < 0) {
        sign = 1;
        n = -n;
    }

    int len = num_len(n);
    
    char * s = malloc(sizeof(char) * (len + 1 + sign));
    char * p = s;
    if (sign) {
    	* p = '-';
    	p ++;
    }

    int num = reverse(n);
   
    while (num) {
    	* p = (num % 10) + '0';
    	num /= 10;
    	p ++;
    }

	while (n % 10 == 0) {
		* p = '0';
		p++;
		n /= 10;
	}
	
    * p = '\0';
   
    return s;
}


int my_strlen(char * s) {
    int len = 0;
    char * p = s;

    while (* p != '\0') {
        len++;
        p++;
    }

    return len;
}

void my_memcpy(char * s1, char * s2, int len) {
	for (int i = 0; i < len; i++) {
		s1[i] = s2[i];
	}
}

char * my_strcat(char * s1, char * s2) {
    int l1 = my_strlen(s1);
    int l2 = my_strlen(s2);

    char * s3 = malloc(sizeof(char) * (l1 + l2 + 1));

    my_memcpy(s3, s1, l1);
    my_memcpy(s3 + l1, s2, l2 + 1);

    return s3;
}

char * my_readline(char * msg) {
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

char * my_strncat(char * str, char c) {
	char * add = malloc(sizeof(char) * 2);
	add[0] = c;
	add[1] = '\0';
	char * tmp = str;
	str = my_strcat(str, add);
	free(tmp);
	free(add);
	return str;
}


char * my_strtok(char ** s, char * ds) {

	if (*s == NULL || my_strlen(*s) == 0) {
		return NULL;
	}
		
	char * p = *s;
	char * buf = NULL;

	while (*p != '\0') {
	
		if (buf != NULL && my_strlen(buf) != 0) {
			for (char * dp = ds; * dp != '\0'; dp++) {
			
				if (*dp == *p) {
				
					char * new = malloc(sizeof(char) * 1);
					new[0] = '\0';
					
					for (char * np = p + 1; * np != '\0'; np++) {
						new = my_strncat(new, *np);
					}

					free(*s);
					*s = new;
					return buf;
				}
			}
		}

		if (buf == NULL) {
			buf = malloc(sizeof(char) * 2);
			buf[0] = * p;
			buf[1] = '\0';
			
		} else {
			buf = my_strncat(buf, *p);
		}
		
		p++;
		
	}	
	
	if (*s != NULL) {
		free(*s);
	}
	*s = NULL;
	return buf;
}

char * my_process_str(char ** str) {
	char * processed = malloc(sizeof(char) * 1);
    * processed = '\0';
	char * token = my_strtok(str, "\t ");
	while (token != NULL) {
       char * tmp = processed;
       if (my_strlen(processed)) {
      	 char * res = my_strcat(" ", token);
	  	 processed = my_strcat(processed, res);
	  	 free(res);
	   } else {
	     processed = my_strcat(processed, token);
	   }
	   free(tmp);
	   free(token);
	   token = my_strtok(str, "\t ");
	}
	free(token);
	
	return processed;
}

int my_solve(char ** str) {
    int summ = 0;
    char op = '+';

    char * token = my_strtok(str, "\t ");
    while (token != NULL) {
        if (my_strlen(token) == 1 && (token[0] == '+' || token[0] == '-')) {
            op = token[0];
        } else {
            int num = my_atoi(token);
            summ += (op == '+' ? num : -num);
        }
        free(token);
        token = my_strtok(str, "\t ");
    }   
    free(token);
	
    return summ;
}

char * my_id(char ** s) {
    char * tmp = malloc(sizeof(char) * (my_strlen(*s) + 1));
    my_memcpy(tmp, *s, my_strlen(*s) + 1);

    int n = my_solve(s);
    char * n_s = my_itoa(n);
    char * res_s = my_strcat(" = ", n_s);
    char * res = my_strcat(tmp, res_s);

    free(n_s);
    free(res_s);
    free(tmp);

    return res;
}
