#include <stdio.h>

#include <math.h>

double calc_eps(double x, double eps, int* n) {

    double t = 8 * x * x * x / 6;
    double s = t;
    int fct = 3;
    long long mlt = 9;
    double last = 0;

    while (fabs(last - s) > eps) {
        last = s;
        t = (-t) / (mlt - 1) * (9 * mlt - 1) * x * x / (fct + 1) / (fct + 2);
        s += t;
        fct += 2;
        mlt *= 9;
        *n += 1;
    }
    
    return 3 * s / 4;
}

double calc_iter(double x, int n) {

    double t = 8 * x * x * x / 6;
    double s = t;
    int fct = 3;
    long long mlt = 9;

    for (int i = 0; i < n; i++) {
        t = (-t) / (mlt - 1) * (9 * mlt - 1) * x * x / (fct + 1) / (fct + 2);
        s += t;
        fct += 2;
        mlt *= 9;
    }
    
    return 3 * s / 4;
}

int main() {
    int mode = 0;
    printf("Enter program mode: 1 - count with iteration count, 2 - count with epsilon.\n");

    while (scanf("%d", &mode) != 1 || (mode != 1 && mode != 2)) {
        while (getchar() != '\n') {}
        fflush(stdin);
        printf("Invalid mode input. Enter 1 or 2.\n");
    }

    double x;
    int n = 0;

    switch (mode) {

    case 1:
        printf("Enter x and n\n");

        while (scanf("%lf %d", &x, &n) != 2 || n < 1) {
            while (getchar() != '\n') {}
            
            fflush(stdin);

            if (n < 1) {
                printf("Iteration count must be at least 1.\n");
            }
            printf("Enter again.\n");
        } 

        printf("Calculated - %.15lf Math.h value - %.15lf\n", calc_iter(x, n), sin(x) * sin(x) * sin(x));
        return 0;

    case 2:
        printf("Enter x and epsilon\n");
        double eps;

        while (scanf("%lf %lf", &x, &eps) != 2 || eps < 0) {
            while (getchar() != '\n') {}
            fflush(stdin);

            if (eps <= 0) {
                printf("Epsilon must be bigger than 0.\n");
            }
            printf("Enter again.\n");
        } 

        printf("Calculated - %.15lf Math.h - %.15lf\n", calc_eps(x, eps, &n), sin(x) * sin(x) * sin(x));
        printf("%d steps required\n", n);
        return 0;
    }
}
