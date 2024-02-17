#include <stdio.h>

int main() {

    int m;
    scanf("%d", &m);

    double t = 1.0;
    double s = 0.0;
    
    for (int k = 1; k <= m; k++) {
        t = (-t) * 2 / k / (k + 1);
        s += t;
    }

    printf("%.15lf\n", s);
    return 0;
}