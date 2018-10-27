#include <stdio.h>
#include <assert.h>
#include <memory.h>

long long combi(long long int n, long long int k) {
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
    long long int result = (combi(2 * n + 2 * m, n + m) * combi(n + m, n)) / (n + m + 1);
    printf("result of two: %lld\n", result);
    return result;
}

long long int countAllThree(int m, int n, int o) {
    long long int result =
            (combi(2 * m + 2 * n + 2 * o, m + n + o) * combi(m + n + o, m) * combi(n + o, o)) / (n + m + o + 1);
    printf("result of three: %lld\n", result);
    return result;
}

long long int countTwoWithSuffix(int n, int m, const char* suffix){
    long long int countN = 0, countM = 0;
    for (unsigned int i = 0 ; i < strlen(suffix) ; i++){
        if (suffix[i] == '(' && suffix[i+1] == ')'){
            n--;
            i++;
        } else if (suffix[i]  == '[' && suffix[i+1]  == ']'){
            m--;
            i++;
        } else if (suffix[i] == ')'){
            countN++;
        } else if (suffix[i]  == ']' ){
            countM++;
        }
    }
    long long int result = (combi(2 * n + 2 * m, n + m) * combi(n + m - (countN+countM), n-countM)) / (n + m + 1);
    printf("result of two with suffix: %lld\n", result);
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
    assert(countTwoWithSuffix(1,2,"[]") == 4); //nefunguje, protoze suffixova funkce nefunguje
    assert(countAllThree(2,1,1) == 168);
    return 0;
}