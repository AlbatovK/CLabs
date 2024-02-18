#include <stdio.h>

#include <stdlib.h>

#include "matrix.h"

int create_test_file_if_not_exist() {
    FILE *file_ptr;
    file_ptr = fopen("test.bin", "wb");

    if (file_ptr == NULL) {
        printf("Unable to open file %s.\n", "test");
        return 0;
    }

    int linesCount = 1;
    fwrite(&linesCount, sizeof(int), 1, file_ptr);
    int size;
    printf("Enter size.\n");
    scanf("%d", &size);
    fwrite(&size, sizeof(int), 1, file_ptr);

    for (int i = 0; i < size; i++) {
        int elem;
        scanf("%d", &elem);
        fwrite(&elem, sizeof(int), 1, file_ptr);
    }

    fclose(file_ptr);
}

int main() {
    
    // Matrix *matrix = malloc(sizeof(Matrix));

    // input(matrix);
    // output(*matrix);
    // erase(matrix);

    // free(matrix);

    create_test_file_if_not_exist();
    ind_task_additional();
    return 0;
}
