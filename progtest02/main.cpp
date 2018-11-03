#include <iostream>
#include <cmath>

using namespace std;

bool readInterval(long long int &firstBack, long long int &lastBack, char &typeBack, int &baseBack) {
    char r, left, right, doubledot, semicolon, type;
    long long int first, last;
    int base = -1;

    cin >> r;
    if (r == 'r') {
        cin >> base >> doubledot >> left >> first >> semicolon >> last >> right >> type;
        if (doubledot != ':' || base < 2 || base > 36) {
            return false;
        }
    } else if (r == '<') {
        cin >> first >> semicolon >> last >> right >> type;
    } else {
        return false;
    }

    if (right != '>' || semicolon != ';' || (type != 'l' && type != 'z' && type != 's') ||
        first < 0 || last < 0 || last < first || cin.fail()) {
        return false;
    }


    firstBack = first;
    lastBack = last;
    typeBack = type;
    baseBack = (base == -1) ? 10 : base;
    return true;
}

long long int countDigits(long long int first, long long int last, int base) {
    long long int result = 0;
    for ( long long int i = first; i <= last; ++i ) {
        if (i == 0 || i == 1) {
            result += 1;
        } else {
            // cout << i << ": " << result << " + " << ceil(log(i) / log(base)) << " = " << result + (long long int)((double)log(i) / log((double)base))+1 << endl;
            result += (long long int) (log((double) i) / log((double) base)) + 1;
        }
    }

    //cout << "RESULT: " << result << endl;
    return result;
}

long long int zeroCount(long long int x, int base) {
    long long int result = 0;
    if (x == 0) return 1;
    while ( x ) {
        if (x % base == 0) result++;
        x /= base;
    }
    return result;
}

long long int countZeros(long long int first, long long int last, int base) {
    long long int result = 0;
    for ( long long int i = first; i <= last; ++i ) {
      //  cout << i << ": " << result << " + " << zeroCount(i, base) << " = " << result + zeroCount(i, base) << endl;
        result += zeroCount(i, base);
    }

    //cout << "RESULT: " << result << endl;
    return result;


}

int main() {
    while ( !cin.eof()) {
        long long int first, last;
        int base = 0;
        char type;
        if (!readInterval(first, last, type, base)) {
            cout << "Nespravny vstup." << endl;
            return 1;
        }

        //cout << "DEBUG: Base: " << base << ", First: " << first << ", Last: " << last << ", Type:  " << type << endl;

        if (type == 'l') {
            cout << "Cifer: " << countDigits(first, last, base) << endl;
        } else if (type == 'z') {
            cout << "Nul: " << countZeros(first, last, base) << endl;
        } else if (type == 's') {
            //   cout << "Sekvence: " << countZeroSeq(first, last, base) << endl;
        }


    }

    return 0;
}