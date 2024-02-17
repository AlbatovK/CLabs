#include <stdio.h>

int fac(int n) {

    if (n <= 1) {
        return 1;
    }

    int p = 1;
    for (int i = 1; i < n; i++) 
        p *= i;
    return p * n;
}

int main() {

    int i = 1;
    while (fac(i) > 0) {
        i++;
    }

    printf("%d %d", i - 1, fac(16));
    return 0;
}