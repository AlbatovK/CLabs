#include "matrix.h"

#include <stdio.h>

#include <stdlib.h>

#include <limits.h>

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

int ind_task() {
    const char *pr = "";
    Line line = {0, NULL};

    printf("Enter vector size.\n");
    do {
        printf("%s", pr);
        pr = "Size must be more than 0.\n";
        getInt(&line.size);
    } while (line.size < 1);

    line.arr = (int *)malloc(line.size * sizeof(int));

    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    matrix->linesCount = line.size;
    matrix->lines = (Line *)malloc(line.size * sizeof(Line));

    printf("Enter elements:\n");

    int mx = INT_MIN;
    for (int i = 0; i < matrix->linesCount; i++) {
        pr = "";
        do {
            printf("%s", pr);
            pr = "Values must be greater or equal to zero.\n";
            getInt(line.arr + i);
            if (line.arr[i] > mx) {
                mx = line.arr[i];
            }
        } while (line.arr[i] < 0);
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

    for (int i = 0; i < matrix->linesCount; i++) {
        int sm = line.arr[i];
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

    for (int i = 0; i < matrix->linesCount; i++) {
        int sm = line.arr[i];
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
    for (int i = 0; i < matrix->linesCount; i++) {
        printf("%d ", line.arr[i]);
    }

    printf("\n\nOutput matrix:\n");
    output(*matrix);

    erase(matrix);
    free(matrix);
    free(f_arr);
    free(line.arr);
}

int ind_task_additional() {
    FILE *file_ptr;
    char filename[100];

    printf("Enter input file name with vector (1 x N matrix):\n");
    scanf("%s", filename);

    file_ptr = fopen(filename, "rb");

    if (file_ptr == NULL) {
        printf("Unable to open file %s.\n", filename);
        return 0;
    }

    Line line = {0, NULL};
    fread(&line.size, sizeof(int), 1, file_ptr);
    printf("Vector lines - %d (Must be 1).\n", line.size);

    int mx = INT_MIN;
    for (int i = 0; i < line.size; i++) {
        int size;
        fread(&size, sizeof(int), 1, file_ptr);
        printf("Vector size - %d\n", size);

        for (int j = 0; j < size; j++) {
            int element;
            fread(&element, sizeof(int), 1, file_ptr);
            printf("%d ", element);
            if (element > mx) {
                mx = element;
            }
        }

        printf("\nEnter output file name for matrix:\n");
        scanf("%s", filename);

        FILE *output_file = fopen(filename, "wb");
        if (output_file == NULL) {
            printf("Unable to open file %s.\n", filename);
            fclose(file_ptr);
            return 0;
        }

        fwrite(&size, sizeof(int), 1, output_file);
        printf("Output matrix lines_count - %d.\n", size);
        fseek(file_ptr, sizeof(int) * 2, SEEK_SET);

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

        for (int i = 0; i < size; i++) {
            int elem;
            fread(&elem, sizeof(int), 1, file_ptr);
            int sm = elem;
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

            fwrite(&k, sizeof(int), 1, output_file);
            printf("Size of %d row - %d.\n", i + 1, k);

            sm = elem;
            j = f_c - 1;

            while (sm > 0) {
                if (sm < f_arr[j]) {
                    j--;
                } else {
                    sm -= f_arr[j];
                    fwrite(f_arr + j, sizeof(int), 1, output_file);
                    printf("%d ", f_arr[j]);
                }
            }
            printf("\n");
        }

        printf("\nLong enough fibbonachi sequence:\n");
        for (int i = 0; i < f_c; i++) {
            printf("%d ", f_arr[i]);
        }

        free(f_arr);

        fclose(output_file);
    }

    fclose(file_ptr);
    return 1;
}