#include <stdlib.h>
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int * arr = malloc(sizeof(int) * n);
    
    for (int * i = arr; i < arr + n; i++) {
        scanf("%d", i);
    }

    int i = 0, j = 0;
    
    while (j < n) {
        if (arr[i] % 2 == 0) {
            j++;
            i++;
        } else {
            if (arr[j] % 2 == 0) {
                int t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            } else {
                j++;
            }
        }
    }

    for (int * i = arr; i < arr + n; i++) {
        printf("%d ", *i);
    }

    return 0;
}