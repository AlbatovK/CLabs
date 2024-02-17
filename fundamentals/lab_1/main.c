#include <stdio.h>

// Счет количества разрядов в числе
int getDigitsCount(int n) {

    int digitsCount = 0;

    while (n != 0) {
        n /= 10;
        digitsCount += 1;
    }

    return digitsCount;

}

// Модуль числа
int abs(int n) {
    return n < 0 ? -n : n;
}

// Сложность алгоритма по памяти O(1); Сложность алгоритма по времени O(2 * log10(N));
int main() {

    // Целочисленные переменные со знаком
    int n;
    int r, s;

    // Целочисленный ввод
    printf("Enter three numbers: n, r, s\n");
    if ( !scanf("%d %d %d", &n, &r, &s) ) {
        printf("Wrong input format.\n");
        return -1;
    }

    // Получение модуля числа, так как сумма цифр не зависит от знака числа
    n = abs(n);

    // Значения r или s меньше нуля
    if (r < 0 || s < 0) {
        printf("Invalid value: r or s is less than zero.\n");
        return -1;
    }

    // Проверка, если r или s больше больше числа разрядов
    int digitsCount = getDigitsCount(n);
    if (digitsCount < r || digitsCount < s) {
        printf("Invalid value: r or s is greater than number digits count.\n");
        return -1;
    }

    int sum_s, sum_r;
    sum_s = sum_r = 0; // Суммы старших и младших цифр

    int curCount = 0; // Позиция текущего разряда, считая с конца

    while (n != 0) {

        curCount++;

        unsigned short digit = n % 10; // Последняя цифра числа
        if (curCount <= r) {
            sum_r += digit;
        }

        if (digitsCount - s < curCount) {
            sum_s += digit;
        }

        n /= 10; // Удаление последнего разряда

    }

    printf("Sum of last %d digits - %d\n", r, sum_r);
    printf("Sum of first %d digits - %d\n", s, sum_s);

    return 0;

}