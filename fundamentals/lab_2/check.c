#include <stdio.h>
#include <math.h>

int getFloat(float *res){
    printf("Type in number\n");
    int f = 0;
    while(!f) {
        f = scanf("%f", res);
        if(f == 0) {
            printf("Wrong input. Try again\n");
            while (getchar() != '\n') {}
            fflush(stdin);
        }
        if(f == EOF) {
            printf("EOF\n");
            return 0;
        }
    }
    return 1;
}

int main() {
    float a = 0;
    getFloat(&a);
    printf("%f", a);
    return 0;
}