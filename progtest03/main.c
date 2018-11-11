#ifndef __PROGTEST__

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#endif /* __PROGTEST__ */

// Source: GeeksForGeeks, modified
long long int extendedGCD(long long int a, long long int b,
                          long long int * x, long long int * y) {
    if (a > b) {
        long long int tmp = a;
        a = b;
        b = tmp;
    }

    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    } else if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    long long int x1, y1;
    long long int gcd = extendedGCD(b % a, a, &x1, &y1);
    // printf("GCD: %lld, x1: %lld, y1: %lld\n", gcd, x1, y1);
    *x = y1 - (b / a) * x1;
    *y = x1;

    long long int tmp = *x;
    *x = *y;
    *y = tmp;

    return gcd;
}

long long int count1(unsigned long long int length, unsigned long long int s1, unsigned int * c1, unsigned int * c2,
                     unsigned int * c3) {
    if (length % s1 != 0) {
        return 0;
    } else {
        *c1 = (unsigned int) (length / s1);
        *c2 = 0;
        *c3 = 0;
        // printf("c1: %d, c2: %d, c3: %d\n", *c1, *c2, *c3);
        return 1;
    }
}

long long int
count2(unsigned long long int length, unsigned long long int s1, unsigned long long int s2, unsigned int * c1,
       unsigned int * c2, unsigned int * c3) {

    long long int lengthLL = (long long int) length;
    long long int s1LL = (long long int) s1;
    long long int s2LL = (long long int) s2;
    long long int x, y, gcd;

    if (s1LL < s2LL) {
        long long int tmp = s1LL;
        s1LL = s2LL;
        s2LL = tmp;
    }
    gcd = extendedGCD(s1LL, s2LL, &x, &y);

    if (lengthLL % gcd != 0) {
        return 0;
    } else {
        x = x * (lengthLL / gcd);
        y = y * (lengthLL / gcd);
    }



    printf("%lld * %lld + %lld * %lld = %lld\n", x, s1LL, y, s2LL, lengthLL);


    *c3 = 0;
    return 0;
}


long long int
count3(unsigned long long int length, unsigned long long int s1, unsigned long long int s2, unsigned long long int s3,
       unsigned int * c1, unsigned int * c2, unsigned int * c3) {
    return 0;
}

unsigned long long int
hyperloop(unsigned long long int length, unsigned int s1, unsigned int s2, unsigned int s3, unsigned int bulkhead,
          unsigned int * c1, unsigned int * c2, unsigned int * c3) {

    if (bulkhead == length) {
        *c1 = *c2 = *c3 = 0;
        return 1;
    }
    if (bulkhead > length) {
        return 0;
    }

    if (s1 == s2) {
        s2 = 0;
    }
    if (s1 == s3) {
        s3 = 0;
    }
    if (s2 == s3) {
        s3 = 0;
    }

    // printf("1: %d, 2: %d, 3: %d\n", s1, s2, s3);

    if (s1 && s2 && s3) {
        unsigned long long int result = (unsigned long long int) count3(length - bulkhead, s1 + bulkhead, s2 + bulkhead,
                                                                        s3 + bulkhead, c1, c2,
                                                                        c3);
        printf("Result 1: %lld\n", result);
        return result;
    } else if (s1 && s2) {
        unsigned long long int result = (unsigned long long int) count2(length - bulkhead, s1 + bulkhead, s2 + bulkhead,
                                                                        c1, c2, c3);
        printf("Result 2: %lld\n", result);
        return result;
    } else if (s1 && s3) {
        unsigned long long int result = (unsigned long long int) count2(length - bulkhead, s1 + bulkhead, s3 + bulkhead,
                                                                        c1, c3, c2);
        printf("Result 3: %lld\n", result);
        return result;
    } else if (s2 && s3) {
        unsigned long long int result = (unsigned long long int) count2(length - bulkhead, s2 + bulkhead, s3 + bulkhead,
                                                                        c2, c3, c1);
        printf("Result 4: %lld\n", result);
        return result;
    } else if (s1) {
        return (unsigned long long int) count1(length - bulkhead, s1 + bulkhead, c1, c2, c3);
    } else if (s2) {
        return (unsigned long long int) count1(length - bulkhead, s2 + bulkhead, c2, c1, c3);
    } else if (s3) {
        return (unsigned long long int) count1(length - bulkhead, s3 + bulkhead, c3, c1, c2);
    }

    return 0;
}

#ifndef __PROGTEST__

int main(int argc, char * argv[]) {
    unsigned int c1, c2, c3;
    assert (hyperloop(27, 9, 9, 9, 0, &c1, &c2, &c3) == 1
            && (9 * c1 + 9 * c2 + 9 * c3) == 27);

    assert (hyperloop(27, 3, 9, 3, 0, &c1, &c2, &c3) == 2
            && (3 * c1 + 9 * c2 + 0 * c3) == 27);

    assert (hyperloop(100, 4, 7, 5, 0, &c1, &c2, &c3) == 42
            && 4 * c1 + 7 * c2 + 5 * c3 + 0 * (c1 + c2 + c3 + 1) == 100);
    assert (hyperloop(12345, 8, 3, 11, 3, &c1, &c2, &c3) == 82708
            && 8 * c1 + 3 * c2 + 11 * c3 + 3 * (c1 + c2 + c3 + 1) == 12345);

    c1 = 8;
    c2 = 9;
    c3 = 10;

    assert (hyperloop(127, 12, 8, 10, 0, &c1, &c2, &c3) == 0
            && c1 == 8 && c2 == 9 && c3 == 10);
    assert (hyperloop(127, 12, 8, 10, 3, &c1, &c2, &c3) == 4
            && 12 * c1 + 8 * c2 + 10 * c3 + 3 * (c1 + c2 + c3 + 1) == 127);
    assert (hyperloop(100, 35, 0, 0, 10, &c1, &c2, &c3) == 1
            && c2 == 0 && c3 == 0 && 35 * c1 + 10 * (c1 + 1) == 100);
    assert (hyperloop(100, 35, 0, 35, 10, &c1, &c2, &c3) == 1
            && c2 == 0 && 35 * c1 + 35 * c3 + 10 * (c1 + c3 + 1) == 100);
    assert (hyperloop(100, 35, 35, 35, 10, &c1, &c2, &c3) == 1
            && 35 * c1 + 35 * c2 + 35 * c3 + 10 * (c1 + c2 + c3 + 1) == 100);

    c1 = 42;
    c2 = 43;
    c3 = 44;

    assert (hyperloop(9, 1, 2, 3, 10, &c1, &c2, &c3) == 0
            && c1 == 42 && c2 == 43 && c3 == 44);
    return 0;
}

#endif /* __PROGTEST__ */
