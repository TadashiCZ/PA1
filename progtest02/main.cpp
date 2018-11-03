#include <iostream>
#include <cmath>

using namespace std;

int readInterval(long long int &firstBack, long long int &lastBack, char &typeBack, int &baseBack) {
    char r, left, right, doubledot, semicolon, type;
    long long int first, last;
    int base = -1;

    cin >> r;
    if (cin.eof()) {
        return 0;
    } else if (r == 'r') {
        cin >> base >> doubledot >> left >> first >> semicolon >> last >> right >> type;
        if (left != '<' || doubledot != ':' || base < 2 || base > 36) {
            cout << "Nespravny vstup." << endl;
            return 0;
        }
    } else if (r == '<') {
        cin >> first >> semicolon >> last >> right >> type;
    } else {
        cout << "Nespravny vstup." << endl;
        return 0;
    }

    if (right != '>' || semicolon != ';' || (type != 'l' && type != 'z' && type != 's') ||
        first < 0 || last < 0 || last < first || !cin.good()) {
        cout << "Nespravny vstup." << endl;
        return 0;
    }


    firstBack = first;
    lastBack = last;
    typeBack = type;
    baseBack = (base == -1) ? 10 : base;
    return 1;
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

long long int zeroSeqCount(long long int x, int base) {
    long long int result = 0, max = 0;
    if (x == 0) return 1;
    while ( x ) {
        if (x % base == 0) {
            //cout << result << "++" << endl;
            result++;
        } else {
            //  cout << "result = 0" << endl;
            if (result > max) max = result;
            result = 0;
        }
        x /= base;
    }
    return max;
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

long long int countZeroSeq(long long int first, long long int last, int base) {
    long long int result = 0;
    for ( long long int i = first; i <= last; ++i ) {
        long long int seq = zeroSeqCount(i, base);
        //  cout << i << ": " << result << " vs.  " << seq << endl;
        if (seq > result) {
            result = seq;
        };
    }

    return result;
}

int main() {

    cout << "Zadejte intervaly:" << endl;
    long long int first, last;
    int base = 0;
    char type;


    while (  readInterval(first, last, type, base) ) {
        //cout << "DEBUG: Base: " << base << ", First: " << first << ", Last: " << last << ", Type:  " << type << endl;

        if (type == 'l') {
            cout << "Cifer: " << countDigits(first, last, base) << endl;
        } else if (type == 'z') {
            cout << "Nul: " << countZeros(first, last, base) << endl;
        } else if (type == 's') {
            cout << "Sekvence: " << countZeroSeq(first, last, base) << endl;
        }

        if (cin.eof()) {
            return 0;
        }
    }

    return 0;
}