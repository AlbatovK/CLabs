#include <stdio.h>

#include <math.h>

double calculate(double x, double eps, int* n) {

    double t = 8 * x * x * x / 6;
    double s = t;
    int fct = 3;
    long long mlt = 9;
    double last = 0;

    while (fabs(last - s) > eps) {
        last = s;
        t = t / (mlt - 1) * (9 * mlt - 1) * x * x / (fct + 1) / (fct + 2);
        t = -t;
        s += t;
        fct += 2;
        mlt *= 9;
        *n += 1;
    }
    
    return 3 * s / 4;
}


int main() {
    printf("Enter x and epsilon\n");
    double x;
    double eps;
    int n = 0;

    while (scanf("%lf %lf", &x, &eps) != 2) {
        fflush(stdin);
        printf("Enter again.\n");
    } 

    printf("Calculated - %.20lf Math.h - %.20lf\n", calculate(x, eps, &n), sin(x) * sin(x) * sin(x));
    printf("%d steps required\n", n);
    return 0;
}