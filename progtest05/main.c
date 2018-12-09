#include <stdio.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26

typedef struct highwayPart {
    long long int mFrom;
    long long int mTo;
    double mPrice;
} SPart;

typedef struct highwayPrice {
    SPart * mArray;
    long long int mCount;
    long long int mSize;
} SHighway;


int insertElement(SHighway ** highways, long long int from, long long int to, char letter, double price) {
    int numberLetter = letter - 65; 
    highways[numberLetter]->mArray[highways[numberLetter]->mCount].mPrice = price;
    highways[numberLetter]->mArray[highways[numberLetter]->mCount].mFrom = from;
    highways[numberLetter]->mArray[highways[numberLetter]->mCount].mTo = to;
    highways[numberLetter]->mCount++;

    for ( int i = 0; i < highways[numberLetter]->mCount; ++i ) {
        if (highways[numberLetter]->mArray[i].mFrom >= from )
    }

    if (highways[numberLetter]->mCount >= highways[numberLetter]->mSize) {
        highways[numberLetter]->mSize *= 2;
        highways[numberLetter]->mArray = (SPart *) realloc(highways[numberLetter]->mArray,
                                                           sizeof(SPart) * highways[numberLetter]->mSize);
        if (!highways[numberLetter]->mArray) {
            return 0;
        }
    }

    return 1;
}

int loadInput(SHighway * highways[ALPHABET_SIZE]) {

    for ( int i = 0; i < ALPHABET_SIZE; ++i ) {
        highways[i] = (SHighway *) malloc(sizeof(SHighway));
        highways[i]->mCount = 0;
        highways[i]->mSize = 1;
        highways[i]->mArray = (SPart *) malloc(sizeof(SPart) * highways[i]->mSize);
    }

    printf("Zmeny:\n");
    char c, letter;
    long long int from, to;
    double price;
    if (scanf(" %c", &c) != 1) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    if (c != '{') {
        printf("Nespravny vstup.\n");
        return 1;
    }

    while ( 1 ) {
        if (scanf(" [ %lld - %lld : %c = %lf ] %c", &from, &to, &letter, &price, &c) != 5) {
            printf("Nespravny vstup.\n");
            return 1;
        }

        if (from >= to || (from < 0 || to < 0) || (letter > 90 || letter < 65) || price < 0.0) {
            printf("Nespravny vstup.\n");
            return 1;
        }


        if (!insertElement(highways, from, to, letter, price)) {
            printf("Memory error.\n");
            return 1;
        }

        if (c == ',') {
            continue;
        } else if (c == '}') {
            break;
        } else {
            printf("\n--\n%c\n--\n", c);
            printf("Nespravny vstup.\n");
            return 1;
        }

    }
    return 0;
}

void clearMemory(SHighway * highways[ALPHABET_SIZE]) {
    for ( int i = 0; i < ALPHABET_SIZE; ++i ) {
        free(highways[i]->mArray);
        free(highways[i]);
    }
}


int main() {
    SHighway * highways[ALPHABET_SIZE];

    if (loadInput(highways)) {
        return 1;
    }

    for ( int i = 0; i < ALPHABET_SIZE; ++i ) {
        for ( int j = 0; j < highways[i]->mCount; ++j ) {
            printf(" [ %lld - %lld : %c = %lf ]\n",
                   highways[i]->mArray[j].mFrom, highways[i]->mArray[j].mTo, i + 65, highways[i]->mArray[j].mPrice);
        }
    }


    clearMemory(highways);
    return 0;
}
