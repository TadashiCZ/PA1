#include <stdio.h>
#include <assert.h>


long long int countAllBrackets(long long int firstOpen, long long int firstEnd,
                               long long int secondOpen, long long int secondEnd) {

    long long int result = 0;
    if (firstOpen == 0 && firstEnd == 0 && secondOpen == 0 && secondEnd == 0) {
        return 1;
    }

    if (firstOpen < 0 || secondOpen < 0 || firstEnd < 0 || secondOpen < 0) {
        return 0;
    }
    printf("First open: %lld, first end: %lld, second open: %lld, second end: %lld\n",
           firstOpen, firstEnd, secondOpen, secondEnd);

    if (firstOpen > 0)
        result =+ countAllBrackets(firstOpen - 1, firstEnd, secondOpen, secondEnd);

    if (secondOpen > 0)
        result =+ countAllBrackets(firstOpen, firstEnd, secondOpen - 1, secondEnd);

    if (firstEnd > firstOpen && firstEnd > 0)
        result =+ countAllBrackets(firstOpen, firstEnd - 1, secondOpen, secondEnd);

    if (secondEnd > secondOpen && secondEnd > 0)
        result =+ countAllBrackets(firstOpen, firstEnd, secondOpen, secondEnd - 1);

    printf("Result: %lld\n", result);
    return result;
}


long long int countAll(int n, int m) {
    if (n == 0 && m == 0) return 1;
    if ((n == 1 && m == 0) || (n == 0 && m == 1)) return 1;

    return countAllBrackets(n, n, m, m);
}

int main() {
    //assert(countAll(1, 0) == 1);
    assert(countAll(1, 1) == 4);
    /*assert(countAll(2, 1) == 15);
    assert(countAll(4, 1) == 210);
    assert(countAll(1, 3) == 56);
    assert(countAll(2, 2) == 84);
    assert(countAll(0, 7) == 429);
    assert(countAll(1, 0) == 1);
    assert(countAll(0, 0) == 1);*/


    return 0;
}