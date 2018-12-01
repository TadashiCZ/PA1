#include <iostream>
#include <cmath>

using namespace std;

int GCD(int a, int b) {
    if (a > b) {
        int tmp = a;
        a = b;
        b = tmp;
    }

    if (a == 0) {
        return b;
    } else if (b == 0) {
        return a;
    }
    int gcd = GCD(b % a, a);

    return gcd;
}

typedef struct fraction {
    int mAbove;
    int mBelow;
} SFraction;

void printFraction(SFraction frac) {
    printf("%d/%d\n", frac.mAbove, frac.mBelow);
}

SFraction * loadFraction() {
    char c;
    SFraction * tmp = (SFraction *) malloc(sizeof(SFraction));
    cin >> tmp->mAbove;
    cin >> c;
    cin >> tmp->mBelow;
    if (tmp->mBelow == 0) {
        printf("Error\n");
        free(tmp);
        return NULL;
    }
    return tmp;
}

SFraction * normalizeFraction(SFraction * frac) {
    if (frac->mBelow == 0) {
        printf("Error");
        return NULL;
    }

    if (frac->mBelow == frac->mAbove) {
        frac->mBelow = 1;
        frac->mAbove = 1;
        return frac;
    }

    if (frac->mAbove % frac->mBelow == 0) {
        frac->mAbove /= frac->mBelow;
        frac->mBelow = 1;
        return frac;
    }

    int gcd = GCD(frac->mAbove, frac->mBelow);
    frac->mAbove /= gcd;
    frac->mBelow /= gcd;
    return frac;
}

SFraction sumFractions(SFraction left, SFraction right) {
    SFraction retVal;

    int lcm = (left.mBelow * right.mBelow) / GCD(left.mBelow, right.mBelow);
    retVal.mBelow = lcm;
    retVal.mAbove = (left.mAbove) * (lcm / left.mBelow) + (right.mAbove) * (lcm / right.mBelow);
    normalizeFraction(&retVal);
    return retVal;
}

SFraction substractFractions(SFraction left, SFraction right) {
    SFraction retVal;

    int lcm = (left.mBelow * right.mBelow) / GCD(left.mBelow, right.mBelow);
    retVal.mBelow = lcm;
    retVal.mAbove = (left.mAbove) * (lcm / left.mBelow) - (right.mAbove) * (lcm / right.mBelow);
    normalizeFraction(&retVal);
    return retVal;
}

SFraction multiplyFractions(SFraction left, SFraction right) {
    SFraction retVal;
    retVal.mBelow = left.mBelow * right.mBelow;
    retVal.mAbove = left.mAbove * right.mAbove;
    normalizeFraction(&retVal);
    return retVal;
}

SFraction divideFractions(SFraction left, SFraction right) {
    SFraction retVal;
    retVal.mBelow = left.mBelow * right.mAbove;
    retVal.mAbove = left.mAbove * right.mBelow;
    normalizeFraction(&retVal);
    return retVal;
}

SFraction expFraction(SFraction frac, int exp) {
    SFraction copy = frac;
    if (exp == 0) {
        frac.mAbove = 1;
        frac.mBelow = 1;
        return frac;
    }
    if (exp == 1) {
        return frac;
    }

    while ( exp != 0 ) {
        if (exp == 1) {
            copy = multiplyFractions(copy, frac);
            exp /= 2;
        } else if (exp % 2 == 0) {
            copy = multiplyFractions(copy, frac);
            exp /= 2;
        } else {
            copy = multiplyFractions(multiplyFractions(copy, frac), frac);
            exp /= 2;
        }

    }

    normalizeFraction(&copy);
    return copy;
}

int main() {
    printf("Zadavej vstupy +, -, /, * a ^, vypni cimkoliv jinym:\n");
    char c;
    while ( 1 ) {
        scanf(" %c", &c);
        if (c == '+') {
            SFraction * left = loadFraction();
            SFraction * right = loadFraction();
            if (!left || !right) {
                free(left);
                free(right);
                continue;
            }
            printFraction(sumFractions(*left, *right));
            free(left);
            free(right);
        } else if (c == '-') {
            SFraction * left = loadFraction();
            SFraction * right = loadFraction();
            if (!left || !right) {
                free(left);
                free(right);
                continue;
            }
            printFraction(substractFractions(*left, *right));
            free(left);
            free(right);
        } else if (c == '/') {
            SFraction * left = loadFraction();
            SFraction * right = loadFraction();
            if (!left || !right) {
                free(left);
                free(right);
                continue;
            }
            printFraction(divideFractions(*left, *right));
            free(left);
            free(right);
        } else if (c == '*') {
            SFraction * left = loadFraction();
            SFraction * right = loadFraction();
            if (!left || !right) {
                free(left);
                free(right);
                continue;
            }
            printFraction(multiplyFractions(*left, *right));
            free(left);
            free(right);
        } else if (c == '^') {
            SFraction * left = loadFraction();
            if (!left) {
                free(left);
                continue;
            }
            int exp;
            scanf("%d", &exp);
            printFraction(expFraction(*left, exp));
            free(left);
        } else {
            break;
        }
    }

    return 0;
}