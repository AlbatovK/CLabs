#include <stdio.h>

#include <math.h>

double e_eps(double x, double eps) {
    double s = 1;
    double t = 1;
    int i = 1;

    while (fabs(t) > eps) {
        t *= x;
        t /= i;
        t = -t;
        s += t;
        i += 1;
    }

    return s;
}

double e_n(double x, int n) {
    double s = 1;
    double t = 1;
    for (int i = 1; i < n + 1; i++) {
        t *= x;
        t /= i;
        t = -t;
        s += t;
    }

    return s;
}

int main() {
    double eps, x;
    scanf("%lf %lf", &eps, &x);
    printf("%lf", e_eps(x, eps));
    int n;
    scanf("%d", &n);
    printf("%lf", e_n(x, n));
}