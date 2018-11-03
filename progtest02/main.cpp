#include <iostream>

using namespace std;

bool readInterval(long long int &firstBack, long long int &lastBack, char & typeBack, int & baseBack) {
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

        if (type == 'l'){
            cout << "Cifer: " << countCiphers(first, last, base) << endl;
        } else if (type == 'z'){
           cout << "Nul: " <countZeros(first, last, base) << endl;
        } else if (type == 's'){
            cout << "Sekvence: " <countZeroSeq(first, last, base) << endl;
        }


    }

    return 0;
}