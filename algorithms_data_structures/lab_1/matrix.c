#include "matrix.h"

#include <stdio.h>

#include <limits.h>

#include <stdlib.h>

int getInt(int *a) {
    int n;
    do {
        n = scanf("%d", a);
        if (n < 0) {
            return 0;
        }
        if (n == 0) {
            printf("Invalid input. Enter again.\n");
            scanf("%*c");
        }
    } while (n == 0);
    return 1;
}

void output(Matrix matrix) {
    for (int i = 0; i < matrix.linesCount; i++) {
        for (int j = 0; j < matrix.lines[i].size; j++) {
            printf("%d ", matrix.lines[i].arr[j]);
        }
        printf("\n");
    }
}

void erase(Matrix *matrix) {
    for (int i = 0; i < matrix->linesCount; i++) {
        free(matrix->lines[i].arr);
    }
    free(matrix->lines);
    matrix->linesCount = 0;
    matrix->lines = NULL;
}

int input(Matrix *matrix) {
    int linesCount = 0;
    const char *pr = "";

    printf("Enter lines count.\n");

    do {
        printf("%s", pr);

        pr = "Lines count must be more than 0.\n";
        if (getInt(&linesCount) == 0) {
            return 0;
        }

    } while (linesCount < 1);

    matrix->linesCount = linesCount;
    matrix->lines = (Line *)calloc(matrix->linesCount, sizeof(Line));

    for (int i = 0; i < matrix->linesCount; i++) {
        int lineSize;
        pr = "";

        printf("Enter line size for line %d.\n", i + 1);

        do {
            printf("%s", pr);

            pr = "Lines count must be more than 0.\n";

            if (getInt(&lineSize) == 0) {
                matrix->linesCount = i;
                erase(matrix);
                return 0;
            }

        } while (lineSize < 1);

        matrix->lines[i].size = lineSize;
        matrix->lines[i].arr = malloc(lineSize * sizeof(int));

        printf("Enter line items for line %d.\n", i + 1);

        for (int j = 0; j < lineSize; j++) {
            int item;

            if (getInt(&item) == 0) {
                matrix->linesCount = i + 1;
                erase(matrix);
                return 0;
            }

            matrix->lines[i].arr[j] = item;
        }
    }

    return 1;
}

void ind_task() {
    int m;
    const char *pr = "";

    printf("Enter vector size.\n");
    do {
        printf("%s", pr);
        pr = "Size must be more than 0.\n";
        getInt(&m);
    } while (m < 1);

    int *arr = (int *)malloc(m * sizeof(int));

    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    matrix->linesCount = m;
    matrix->lines = (Line *)malloc(m * sizeof(Line));

    printf("Enter elements:\n");

    int mx = INT_MIN;
    for (int i = 0; i < m; i++) {
        pr = "";
        do {
            printf("%s", pr);
            pr = "Values must be greater or equal to zero.\n";
            getInt(arr + i);
            if (arr[i] > mx) {
                mx = arr[i];
            }
        } while (arr[i] < 0);
    }

    int f_c = 2;
    int a = 1, b = 1;
    while (b < mx) {
        int tmp = b;
        b = a + b;
        a = tmp;
        f_c += 1;
    }

    int *f_arr = (int *)malloc(f_c * sizeof(int));
    f_arr[0] = f_arr[1] = 1;
    for (int i = 2; i < f_c; i++) {
        f_arr[i] = f_arr[i - 1] + f_arr[i - 2];
    }

    for (int i = 0; i < m; i++) {
        int sm = arr[i];
        int j = f_c - 1;
        int k = 0;

        while (sm > 0) {
            if (sm < f_arr[j]) {
                j--;
            } else {
                sm -= f_arr[j];
                k += 1;
            }
        }
        matrix->lines[i].size = k;
        matrix->lines[i].arr = (int *)malloc(k * sizeof(int));
    }

    for (int i = 0; i < m; i++) {
        int sm = arr[i];
        int j = f_c - 1;
        int k = 0;
        while (sm > 0) {
            if (sm < f_arr[j]) {
                j--;
            } else {
                sm -= f_arr[j];
                matrix->lines[i].arr[k] = f_arr[j];
                k += 1;
            }
        }
    }

    printf("\n\nLong enough fibbonachi sequence:\n");
    for (int i = 0; i < f_c; i++) {
        printf("%d ", f_arr[i]);
    }

    printf("\n\nInput vector:\n");
    for (int i = 0; i < m; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n\nOutput matrix:\n");
    output(*matrix);

    erase(matrix);
    free(matrix);
    free(f_arr);
    free(arr);
}