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

int input(Matrix *);

void output(Matrix);

void erase(Matrix *);

int ind_task();

int ind_task_additional();

#endif