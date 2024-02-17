#include <stdio.h>
#include <math.h>


int main() {
    int n;
    scanf("%d", &n);
    for (int i = 3; i <= n; i += 2) {
        int flag = 1;
        for (int j = 3; j <= sqrt(i) + 1; j += 2) {
            if (i % j == 0) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            printf("%d\n", i);
        }
    }
    return 0;
}