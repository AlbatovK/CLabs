#ifndef MATRIX_H
#define MATRIX_H

typedef struct Line {
    int size;
    int *arr;
} Line;

typedef struct Matrix {
    int linesCount;
    Line *lines;
} Matrix;

int getInt(int *);

void output(Matrix);

void erase(Matrix *);

void ind_task();

#endif