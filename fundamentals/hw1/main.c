#include <stdio.h>


int reverse(int n) {
    
    int res = 0;
    
    while (n) {
        res *= 10;
        res += n % 10;
        n /= 10;
    }

    return res;

}

int main() {
    int n;
    scanf("%d", &n);

    int t = 0;
    while (n != t) {
        n += t;
        t = reverse(n);
    }
    
    printf("%d", n);

    return 0;
}