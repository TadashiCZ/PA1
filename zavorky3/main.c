#include <stdio.h>
#include <assert.h>

unsigned long int catalanDP(unsigned int n) {
    // Table to store results of subproblems
    unsigned long int catalan[n + 1];

    // Initialize first two values in table
    catalan[0] = catalan[1] = 1;

    // Fill entries in catalan[] using recursive formula
    for (int i = 2; i <= n; i++) {
        catalan[i] = 0;
        for (int j = 0; j < i; j++)
            catalan[i] += catalan[j] * catalan[i - j - 1];
    }
    // Return last entry
    return catalan[n];
}

long long combi(int n, int k) {
    long long ans = 1;
    if (k > n - k)
        k = n - k;
    
    int i = 1;
    for (; i <= k; i++, n--) {
        if (n % i == 0) {
            ans *= n / i;
        } else if (ans % i == 0) {
            ans = ans / i * n;
        } else {
            ans = (ans * n) / i;
        }
    }
    return ans;
}


long long int countAll(int n, int m) {
    long long int result = (combi(2*n+2*m, n+m) * combi(n+m, n))  / (n+m+1);
    printf("%lld\n", result);
    return result;
}

int main() {
    assert(countAll(0, 0) == 1);
    assert(countAll(1, 1) == 4);
    assert(countAll(2, 1) == 15);
    assert(countAll(4, 1) == 210);
    assert(countAll(1, 3) == 56);
    assert(countAll(2, 2) == 84);
    assert(countAll(0, 7) == 429);
    assert(countAll(1, 0) == 1);
    assert(countAll(0, 0) == 1);


    return 0;
}