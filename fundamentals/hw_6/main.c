#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "readline.h"

typedef struct {
    char * brand;
    char * number;
    int distance;
} car_t;


int main(void) {
    printf("Input array length.\n");
    int n;
    scanf("%d", &n);

    car_t * arr = malloc(sizeof(car_t) * n);

    for (int i = 0; i < n; i++) {
        printf("Print car details:\n");
        car_t car;

        car.brand = readline("");
        car.number = readline("");
        scanf("%d", &car.distance);
        arr[i] = car;
    }

    int str_size = 0;
    char ** s = malloc(sizeof(char *) * str_size);

    printf("Choose brand:\n");
    for (int i = 0; i < n; i++) {
        char * brand = arr[i].brand;

        int found = 0;
        for (int j = 0; j < str_size; j++) {
            if (strcmp(s[j],  brand) == 0) {
                found = 1;
            }
        }

        if (!found) {
            str_size++;
            s = realloc(s, sizeof(char *) * str_size);
            s[str_size - 1] = strdup(brand);
            printf("%s ", brand);
        }
    }

    printf("\nEnter brand:\n");
    char * brand = readline("");
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].brand, brand) == 0) {
            printf("%s %s %d\n", arr[i].brand, arr[i].number, arr[i].distance);
        }
        free(arr[i].brand);
        free(arr[i].number);
    }

    
    free(arr);
    free(s);
    return 0;
}