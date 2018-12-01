#include <iostream>

using namespace std;

int billboards[1000000];


int loadArray(int * len) {
    char c;

    printf("Mozna umisteni:\n");

    if (scanf("%d", len) != 1) {
        printf("Nespravny vstup.\n");
        return 0;
    }


    if (scanf(" %c", &c) != 1) {
        printf("Nespravny vstup.\n");
        return 0;
    }

    if (c != ':') {
        printf("Nespravny vstup.\n");
        return 0;
    }

    if (scanf(" %c", &c) != 1) {
        printf("Nespravny vstup.\n");
        return 0;
    }
    if (c != '{') {
        printf("Nespravny vstup.\n");
        return 0;
    }

    c = ',';
    int cnt = 1;
    while ( true ) {
        if (cnt > 1000000) {
            printf("Nespravny vstup.\n");
            return 0;
        }

        if (scanf("%d", billboards + cnt) != 1) {
            printf("Nespravny vstup.\n");
            return 0;
        }

        if (billboards[cnt] <= 0 || billboards[cnt] >= *len) {
            printf("Nespravny vstup.\n");
            return 0;
        }

        cnt++;

        if (scanf(" %c", &c) != 1) {
            printf("Nespravny vstup.\n");
            return 0;
        }

        if (c == '}') {
            break;
        }

        if (c != ',') {
            printf("Nespravny vstup.\n");
            return 0;
        }
    }

    billboards[0] = 0;
    billboards[cnt] = *len;
    return cnt;
}

// Michael Burr int compare
int cmpfunc(const void * a, const void * b) {
    return (*(int *) a - *(int *) b);
}

void countBillboards(int input, int count) {
    int cnt = 0;

    int sum = 0;
    for ( int i = 0; i <= count; ++i ) {
        if (billboards[i] > input) {
            cout << "N/A" << endl;
            return;
        }
        if (sum + billboards[i] <= input) {
            sum += billboards[i];
        } else {
            cnt++;
            sum = 0;
            sum += billboards[i];

        }
    }
    if (cnt < count) {
        cout << "Billboardu: " << cnt << endl;
    } else {
        cout << "N/A" << endl;
    }
}

void recalcArrayToDifferences(int count) {
    int tmp = 0, tmp2 = 0;
    for ( int i = 0; i < count + 1; ++i ) {
        tmp = billboards[i];
        if (i != 0) billboards[i] = billboards[i] - tmp2;
        tmp2 = tmp;
    }
}

int main() {
    int len;
    int count = loadArray(&len);

    if (!count) {
        return 1;
    }

    qsort(billboards, static_cast<size_t>(count), sizeof(int), cmpfunc);
    recalcArrayToDifferences(count);


    cout << "Vzdalenosti:" << endl;
    int res = 0;
    int input;
    bool readOne = false;
    while ( true ) {
        if ((res = scanf("%d", &input)) != 1 && res != EOF) {
            printf("Nespravny vstup.\n");
            return 1;
        } else if (res == EOF && readOne) {
            break;
        }
        readOne = true;
        if (input <= 0) {
            printf("Nespravny vstup.\n");
            return 1;
        }

        countBillboards(input, count);

    }

    return 0;
}