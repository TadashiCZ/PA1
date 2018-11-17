#ifndef __PROGTEST__

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#endif /* __PROGTEST__ */

unsigned long long int
count3(unsigned long long int length, unsigned int s1, unsigned int s2, unsigned int s3,
       unsigned int * c1, unsigned int * c2, unsigned int * c3) {
    return 0;
}

unsigned long long int
count2(unsigned long long int length, unsigned int s1, unsigned int s2,
       unsigned int * c1, unsigned int * c2, unsigned int * c3) {
    unsigned long long int segment1 = 0, segment2 = 0, segment3 = 0, found = 0;
    unsigned long long int count = 0, currentLength = 0;

    while ( currentLength < length ) {

        segment1 = (length - currentLength) / s1;
        if ((length - currentLength) == segment1 * s1) {
            

        }

        currentLength += s2;
    }


    return 0;
}

unsigned long long int count1(unsigned long long int length, unsigned int s1,
                              unsigned int * c1, unsigned int * c2, unsigned int * c3) {
    if (length % s1 == 0) {
        *c1 = length / s1;
        *c2 = 0;
        *c3 = 0;
        return 1;
    } else {
        return 0;
    }
}


unsigned long long int
hyperloop(unsigned long long int length, unsigned int s1, unsigned int s2, unsigned int s3, unsigned int bulkhead,
          unsigned int * c1, unsigned int * c2, unsigned int * c3) {
    if (bulkhead > length) return 0;
    if (length == 0) return 0;

    if (s1 == s2 && s2 == s3 && s1 == s3) {
        return count1(length - bulkhead, s1 + bulkhead, c1, c2, c3);
    }

    if (s1 == s2) {
        return count2(length - bulkhead, s1 + bulkhead, s2 + bulkhead, c1, c2, c3);
    } else if (s2 == s3) {
        return count2(length - bulkhead, s2 + bulkhead, s3 + bulkhead, c2, c3, c1);
    } else if (s1 == s3) {
        return count2(length - bulkhead, s1 + bulkhead, s3 + bulkhead, c1, c2, c2);
    }

    return count3(length - bulkhead, s1 + bulkhead, s2 + bulkhead, s3 + bulkhead, c1, c2, c3);


}

#ifndef __PROGTEST__

int main(int argc, char * argv[]) {
    unsigned int c1, c2, c3;
    assert (hyperloop(100, 4, 7, 5, 0, &c1, &c2, &c3) == 42
            && 4 * c1 + 7 * c2 + 5 * c3 + 0 * (c1 + c2 + c3 + 1) == 100);
    assert (hyperloop(12345, 8, 3, 11, 3, &c1, &c2, &c3) == 82708
            && 8 * c1 + 3 * c2 + 11 * c3 + 3 * (c1 + c2 + c3 + 1) == 12345);
    c1 = 8;
    c2 = 9;
    c3 = 10;
    assert (hyperloop(127, 12, 8, 10, 0, &c1, &c2, &c3) == 0
            && c1 == 8
            && c2 == 9
            && c3 == 10);
    assert (hyperloop(127, 12, 8, 10, 3, &c1, &c2, &c3) == 4
            && 12 * c1 + 8 * c2 + 10 * c3 + 3 * (c1 + c2 + c3 + 1) == 127);
    assert (hyperloop(100, 35, 0, 0, 10, &c1, &c2, &c3) == 1
            && c2 == 0
            && c3 == 0
            && 35 * c1 + 10 * (c1 + 1) == 100);
    assert (hyperloop(100, 35, 0, 35, 10, &c1, &c2, &c3) == 1
            && c2 == 0
            && 35 * c1 + 35 * c3 + 10 * (c1 + c3 + 1) == 100);
    assert (hyperloop(100, 35, 35, 35, 10, &c1, &c2, &c3) == 1
            && 35 * c1 + 35 * c2 + 35 * c3 + 10 * (c1 + c2 + c3 + 1) == 100);
    c1 = 42;
    c2 = 43;
    c3 = 44;
    assert (hyperloop(9, 1, 2, 3, 10, &c1, &c2, &c3) == 0
            && c1 == 42
            && c2 == 43
            && c3 == 44);
    return 0;
}

#endif /* __PROGTEST__ */
