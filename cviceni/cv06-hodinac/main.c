#include <stdio.h>
#include <math.h>

int ipow(int x, int n) {
    if (n == 0) {
        return 1;
    }
    int result = x;
    for ( int i = 1; i < n; ++i ) {
        result = result * x;
    }
    return result;

}

void swapToOrder(int * a, int * b) {
    if (*a <= *b) {
        return;
    }
    if (b > a) {
        int temp = *b;
        *b = *a;
        *a = temp;
    }
}

long long int Fibonacci(long long int n) {
    long long int i = 1, result = 1, prevResult = 1;
    while ( i < n - 1 ) {
        long long int temp = result;
        result = result + prevResult;
        prevResult = temp;
        i++;
    }
    return result;
}

void printPrimes(const int * n) {
    int zbytek = *n;
    for ( int i = 2; i <= sqrt(zbytek); i++ ) {
        if (zbytek % i == 0) {
            int counter = 0;
            while ( zbytek % i == 0 ) {
                zbytek = zbytek / i;
                counter++;
            }
            if (counter > 1) {
                printf("%d^%d ", i, counter);
            } else {
                printf("%d ", i);
            }
        }
    }

    if (zbytek > 1) {
        printf("%d ", zbytek);
    }

    printf("\n");
}

int main() {
    /*printf("%d", ipow(2, 3));
    int a = 10, b = 3;

    swapToOrder(&a, &b);
    printf("%d %d\n", a, b);

    printf("%lld\n", Fibonacci(120));*/

    int n = 120;

    printf("Zadej vstup\n");
    scanf("%d", &n);
    printPrimes(&n);

    return 0;
}