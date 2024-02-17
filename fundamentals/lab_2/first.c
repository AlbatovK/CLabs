#include <stdio.h>

#include <math.h>

double calculate(double x, int n) {

    double t = 8 * x * x * x / 6;
    double s = t;
    int fct = 3;
    long long mlt = 9;

    for (int i = 0; i < n; i++) {
        t = t / (mlt - 1) * (9 * mlt - 1) * x * x / (fct + 1) / (fct + 2);
        t = -t;
        s += t;
        fct += 2;
        mlt *= 9;
    }
    
    return 3 * s / 4;
}


int main() {
    
    printf("Enter x and n\n");
    double x;
    int n;

    while (scanf("%lf %d", &x, &n) != 2) {
        fflush(stdin);
        printf("Enter again.\n");
    } 

    if (n < 2) {
        printf("Iteration count must be at least 1.\n");
        return -1;
    }

    printf("Calculated - %.9lf Math.h value - %.9lf\n", calculate(x, n), sin(x) * sin(x) * sin(x));

    return 0;
}