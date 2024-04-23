#ifndef UTILS_H

#define UTILS_H

#include <stdio.h>

char * m_strcat(char * s1, char * s2);

char * m_strdup(char * s);

char * readline();

char * file_readline(FILE * file_ptr);

int getInt(int * a);

#endif
