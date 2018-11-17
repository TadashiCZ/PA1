#ifndef __PROGTEST__

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#endif /* __PROGTEST__ */

void inputSegment(unsigned long long int segment1, unsigned long long int segment2, unsigned long long int segment3,
                  unsigned int * c1, unsigned int * c2, unsigned int * c3) {
    *c1 = (unsigned int) segment1;
    *c2 = (unsigned int) segment2;
    *c3 = (unsigned int) segment3;
}

unsigned long long int
hyperloop3(unsigned long long int length, unsigned int s1, unsigned int s2, unsigned int s3,
           unsigned int * c1, unsigned int * c2, unsigned int * c3) {
    unsigned long long int segment1 = 0, segment2 = 0, segment3 = 0, found = 0;
    unsigned long long int count = 0, currentLength = 0;

    while ( currentLength <= length ) {

        while ( currentLength <= length ) {
            if ((length - currentLength) % s1 == 0) {
                segment1 = (length - currentLength) / s1;
                count++;
                if (!found) {
                    found = 1;
                    inputSegment(segment1, segment2, segment3, c1, c2, c3);
                }
            }

            segment2++;
            currentLength += s2;
        }

        currentLength = currentLength - segment2 * s2;
        segment2 = 0;

        segment3++;
        currentLength += s3;
    }

    return count;
}

unsigned long long int
hyperloop2(unsigned long long int length, unsigned int s1, unsigned int s2,
           unsigned int * c1, unsigned int * c2, unsigned int * c3) {

    unsigned long long int segment1 = 0, segment2 = 0, segment3 = 0, found = 0;
    unsigned long long int count = 0, currentLength = 0;

    while ( currentLength <= length ) {


        if ((length - currentLength) % s1 == 0) {
            segment1 = (length - currentLength) / s1;
            count++;
            if (!found) {
                found = 1;
                inputSegment(segment1, segment2, segment3, c1, c2, c3);
            }
        }

        segment2++;
        currentLength += s2;
    }

    return count;
}

unsigned long long int hyperloop1(unsigned long long int length, unsigned int s1,
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


    if (bulkhead == 0 && length == 0){
        return 0;
    }

   if (bulkhead == length) {
        *c1 = 0;
        *c2 = 0;
        *c3 = 0;
        return 1;
    }

    if (s1 == 0 && s2 == 0 && s3 == 0){
        return 0;
    }

    if (length == 0) return 0;

    if (s1 == s2) {
        s2 = 0;
    }

    if (s1 == s3) {
        s3 = 0;
    }

    if (s2 == s3) {
        s3 = 0;
    }


    if (s1 && !s2 && !s3) {
        return hyperloop1(length - bulkhead, s1 + bulkhead, c1, c2, c3);
    }

    if (!s1 && s2 && !s3) {
        return hyperloop1(length - bulkhead, s2 + bulkhead, c2, c1, c3);
    }

    if (!s1 && !s2 && s3) {
        return hyperloop1(length - bulkhead, s3 + bulkhead, c3, c2, c1);
    }

    if (s1 && s2 && !s3) {
        return hyperloop2(length - bulkhead, s1 + bulkhead, s2 + bulkhead, c1, c2, c3);
    } else if (!s1 && s2 && s3) {
        return hyperloop2(length - bulkhead, s2 + bulkhead, s3 + bulkhead, c2, c3, c1);
    } else if (s1 && !s2 && s3) {
        return hyperloop2(length - bulkhead, s1 + bulkhead, s3 + bulkhead, c1, c3, c2);
    }

    return hyperloop3(length - bulkhead, s1 + bulkhead, s2 + bulkhead, s3 + bulkhead, c1, c2, c3);


}

#ifndef __PROGTEST__

int main(int argc, char * argv[]) {
    unsigned int c1, c2, c3;



    assert ( hyperloop ( 226, 0, 0, 0, 226, &c1, &c2, &c3 ) == 1 && 0 * c1 + 0 * c2 + 0 * c3 + 226 * ( c1 + c2 + c3 + 1 ) == 226 );
    assert ( hyperloop ( 226, 226, 0, 0, 0, &c1, &c2, &c3 ) == 1 && 226 * c1 + 0 * c2 + 0 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 226 );
    assert ( hyperloop ( 226, 0, 226, 0, 0, &c1, &c2, &c3 ) == 1 && 0 * c1 + 226 * c2 + 0 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 226 );
    assert ( hyperloop ( 226, 0, 0, 226, 0, &c1, &c2, &c3 ) == 1 && 0 * c1 + 0 * c2 + 226 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 226 );
    assert ( hyperloop ( 226, 0, 226, 226, 0, &c1, &c2, &c3 ) == 1 && 0 * c1 + 226 * c2 + 226 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 226 );
    assert ( hyperloop ( 226, 226, 0, 226, 0, &c1, &c2, &c3 ) == 1 && 226 * c1 + 0 * c2 + 226 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 226 );
    assert ( hyperloop ( 226, 226, 226, 226, 0, &c1, &c2, &c3 ) == 1 && 226 * c1 + 226 * c2 + 226 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 226 );
    c1 = 42; c2 = 43; c3 = 44;
    assert ( hyperloop ( 9, 0, 0, 0, -1, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
    assert ( hyperloop ( -9, 0, 0, 3, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
    assert ( hyperloop ( 9, 0, 0, 0, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
    assert ( hyperloop ( 9, 0, 0, 0, 3, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
    assert ( hyperloop ( 9, 12, 0, 0, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
    assert ( hyperloop ( 9, 0, 12, 0, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
    assert ( hyperloop ( 9, 0, 0, 12, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
    assert ( hyperloop ( 9, 0, 0, 0, 12, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
    assert ( hyperloop ( 9, 12, 12, 12, 12, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
    assert ( hyperloop ( 9, 12, 0, 12, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
    assert ( hyperloop ( 9, 0, 12, 12, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
    assert ( hyperloop ( 9, 12, 12, 0, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
    assert ( hyperloop ( 9, 0, 0, 12, 12, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
    assert ( hyperloop ( 9, 0, 12, 0, 12, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
    assert ( hyperloop ( 9, 12, 0, 0, 12, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
    assert ( hyperloop ( 9, 12, 0, 0, 12, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
    assert ( hyperloop ( 9, 4, 0, 0, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
    assert ( hyperloop ( 9, 4, 0, 0, 3, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
    assert ( hyperloop ( 0, 0, 0, 0, 0, &c1, &c2, &c3 ) == 0  && c1 == 42 && c2 == 43 && c3 == 44);
    assert ( hyperloop ( 0, 4, 5, 2, 7, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
    assert ( hyperloop ( 9, 3, 2, 0, 0, &c1, &c2, &c3 ) == 2 && 3 * c1 + 2 * c2 + 0 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 9 );
    assert ( hyperloop ( 9, 3, 2, 14, 0, &c1, &c2, &c3 ) == 2 && 3 * c1 + 2 * c2 + 0 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 9 );
    assert ( hyperloop ( 9, 3, 3, 3, 0, &c1, &c2, &c3 ) == 1 && 3 * c1 + 3 * c2 + 3 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 9 );
    assert ( hyperloop ( 9, 1, 1, 1, 0, &c1, &c2, &c3 ) == 1 && 1 * c1 + 1 * c2 + 1 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 9 );
    assert ( hyperloop ( 99999999, 1, 1, 1, 0, &c1, &c2, &c3 ) == 1 && 1 * c1 + 1 * c2 + 1 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 99999999 );
    assert ( hyperloop ( 99999999, 99999997, 0, 0, 1, &c1, &c2, &c3 ) == 1 && 99999997 * c1 + 0 * c2 + 0 * c3 + 1 * ( c1 + c2 + c3 + 1 ) == 99999999 );
    assert ( hyperloop ( 1869, 623, 1246, 1246, 0, &c1, &c2, &c3 ) == 2 && 623 * c1 + 1246 * c2 + 1246 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 1869 );
    assert ( hyperloop ( 1869, 1246, 623, 1246, 0, &c1, &c2, &c3 ) == 2 && 1246 * c1 + 623 * c2 + 1246 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 1869 );
    assert ( hyperloop ( 1869, 1246, 1246, 623, 0, &c1, &c2, &c3 ) == 2 && 1246 * c1 + 1246 * c2 + 623 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 1869 );


    assert (hyperloop ( 2007, 1338, 1338, 669, 0, &c1, &c2, &c3 ) == 2 && 1338 * c1 + 1338 * c2 + 669 * c3 + 0 * (c1 + c2 + c3 + 1) == 2007);

    assert(hyperloop(1, 0, 0, 1, 1, &c1, &c2, &c3) == 1 && c1 == 0 && c2 == 0 && c3 == 0);
    assert (hyperloop(573, 0, 191, 382, 0, &c1, &c2, &c3) == 2);
    assert(hyperloop(226, 0, 0, 0, 226, &c1, &c2, &c3) == 1);


    assert (hyperloop(226, 0, 0, 0, 226, &c1, &c2, &c3) == 1 &&
            0 * c1 + 0 * c2 + 0 * c3 + 226 * (c1 + c2 + c3 + 1) == 226);
    assert (hyperloop(226, 226, 0, 0, 0, &c1, &c2, &c3) == 1 &&
            226 * c1 + 0 * c2 + 0 * c3 + 0 * (c1 + c2 + c3 + 1) == 226);
    assert (hyperloop(226, 0, 226, 0, 0, &c1, &c2, &c3) == 1 &&
            0 * c1 + 226 * c2 + 0 * c3 + 0 * (c1 + c2 + c3 + 1) == 226);
    assert (hyperloop(226, 0, 0, 226, 0, &c1, &c2, &c3) == 1 &&
            0 * c1 + 0 * c2 + 226 * c3 + 0 * (c1 + c2 + c3 + 1) == 226);
    assert (hyperloop(226, 0, 226, 226, 0, &c1, &c2, &c3) == 1 &&
            0 * c1 + 226 * c2 + 226 * c3 + 0 * (c1 + c2 + c3 + 1) == 226);
    assert (hyperloop(226, 226, 0, 226, 0, &c1, &c2, &c3) == 1 &&
            226 * c1 + 0 * c2 + 226 * c3 + 0 * (c1 + c2 + c3 + 1) == 226);
    assert (hyperloop(226, 226, 226, 226, 0, &c1, &c2, &c3) == 1 &&
            226 * c1 + 226 * c2 + 226 * c3 + 0 * (c1 + c2 + c3 + 1) == 226);


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
