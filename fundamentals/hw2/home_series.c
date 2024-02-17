#include <stdio.h>


double calc(double x, int n) {
    double t = -(x / 2);
    double s = t;
    for (int k = 2; k < n; k++) {
        for (int j = 0; j < k; j++) {
            t *= x;
        }
        t = -t;
        t /= k;
        s += t;
    }
    return s;
}

int main() {
    double x;
    int n;
    scanf("%lf %d", &x, &n);
    printf("%lf", calc(x, n));
    return 0;
}