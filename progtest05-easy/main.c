#include <stdio.h>
#include <stdlib.h>


#define ALPHABET_SIZE 26
#define PRINT_ERROR printf("Nespravny vstup.\n");

typedef struct StructPart {
    long long int mKm;
    long long int mFrom;
    long long int mTo;
    double mPrices[ALPHABET_SIZE];
} SPart;

typedef struct StructHighway {
    long long int mSize;
    long long int mCount;
    long long int mLength;
    SPart * mParts;
} SHighway;

void deleteHighway(SHighway * highway) {
    free(highway->mParts);
    free(highway);
}

void printHighway(SHighway * highway) {

    printf("Count: %lld, Size: %lld, Length: %lld\n", highway->mCount, highway->mSize, highway->mLength);
    for ( int i = 0; i < highway->mCount; ++i ) {
        printf("From: %lld, To: %lld, Km: %lld\n", highway->mParts[i].mFrom, highway->mParts[i].mTo,
               highway->mParts[i].mKm);
        char c = 'A';
        for ( int j = 0; j < ALPHABET_SIZE; ++j ) {
            if (highway->mParts[i].mPrices[j] > 0) {
                printf("%c: %lf, ", c, highway->mParts[i].mPrices[j]);
            }
            c++;
        }
        printf("\n");
    }

    printf("\n\n\n");
}

SHighway * loadInput() {
    printf("Myto:\n");
    char c, letter;
    long long int km;
    double price;
    SHighway * highway = (SHighway *) malloc(sizeof(struct StructHighway));

    highway->mLength = 0;
    highway->mCount = 0;
    highway->mSize = 10;
    highway->mParts = (SPart *) calloc((sizeof(SPart) * highway->mSize), 0);

    if (scanf(" %c", &c) != 1) {
        PRINT_ERROR
        deleteHighway(highway);
        return NULL;
    }
    if (c != '{') {
        PRINT_ERROR
        deleteHighway(highway);
        return NULL;
    }

    while ( 1 ) {
        if (scanf(" [ %lld : ", &km) != 1) {
            PRINT_ERROR
            deleteHighway(highway);
            return NULL;
        }

        if (km <= 0) {
            PRINT_ERROR
            deleteHighway(highway);
            return NULL;
        }

        for ( int i = 0; i < ALPHABET_SIZE; ++i ) {
            if (highway->mCount > 0) {
                highway->mParts[highway->mCount].mPrices[i] = highway->mParts[highway->mCount].mPrices[i - 1];
            } else {
                highway->mParts[highway->mCount].mPrices[i] = 0;
            }

        }


        while ( 1 ) {
            if (scanf(" %c", &letter) != 1) {
                PRINT_ERROR
                deleteHighway(highway);
                return NULL;
            }

            printf("1 '%c' \n", letter);

            if (scanf(" %c", &c) != 1) {
                printf("2 ");
                PRINT_ERROR
                deleteHighway(highway);
                return NULL;
            }

            if (c != '='){
                printf("2.5 '%c' \n", c);
                PRINT_ERROR
                deleteHighway(highway);
                return NULL;
            }

            if (scanf("%lf", &price) != 1) {
                printf("3 ");
                PRINT_ERROR
                deleteHighway(highway);
                return NULL;

            }

            if (scanf(" %c", &c) != 1) {
                printf("4 ");
                PRINT_ERROR
                deleteHighway(highway);
                return NULL;
            }

//            if (scanf(" %c = %lf %c", &letter, &price, &c) != 3) {
//                printf("1 ");
//                PRINT_ERROR
//                deleteHighway(highway);
//                return NULL;
//            }

            if ((letter > 90 || letter < 65) || price < 0.0) {
                PRINT_ERROR
                deleteHighway(highway);
                return NULL;
            }

            int numberLetter = letter - 65;

            highway->mParts[highway->mCount].mPrices[numberLetter] = price;

            if (c == ',') {
                continue;
            } else if (c == ']') {
                break;
            } else {
                PRINT_ERROR
                deleteHighway(highway);
                return NULL;
            }

        }

        highway->mParts[highway->mCount].mKm = km;
        highway->mParts[highway->mCount].mFrom = highway->mLength;
        highway->mLength += km;
        highway->mParts[highway->mCount].mTo = highway->mLength;
        highway->mCount++;

        // printHighway(highway);

        if (highway->mCount >= highway->mSize) {
            highway->mSize *= 2;
            highway->mParts = (SPart *) realloc(highway->mParts, sizeof(SPart) * highway->mSize);
            if (highway->mParts == NULL) {
                PRINT_ERROR
                free(highway);
                return NULL;
            }
        }

        if (scanf(" %c", &c) != 1) {
            PRINT_ERROR
            free(highway->mParts);
            free(highway);
            return NULL;
        }

        if (c == ',') {
            continue;
        } else if (c == '}') {
            break;
        } else {
            //  printf("\n--\n%c\n--\n", c);
            PRINT_ERROR
            free(highway->mParts);
            free(highway);
            return NULL;
        }

    }

    return highway;
}

void calculatePrices(SHighway * highway, long long int from, long long int to) {
    double prices[ALPHABET_SIZE];
    for ( int i = 0; i < ALPHABET_SIZE; ++i ) {
        prices[i] = 0.0;
    }

    if (from < to) {
        for ( int i = 0; i < highway->mCount; ++i ) {
            SPart currentPart = highway->mParts[i];
            if (currentPart.mFrom > to) {
                break;
            }

            if (currentPart.mTo < from) {
                continue;
            }

            if (from == currentPart.mFrom && currentPart.mTo == to) {
                // exact fit
                for ( int j = 0; j < ALPHABET_SIZE; ++j ) {
                    prices[j] += currentPart.mPrices[j] * currentPart.mKm;
                }
                break;
            } else if (from > currentPart.mFrom && currentPart.mTo > to) {
                // whole block is inside interval
                for ( int j = 0; j < ALPHABET_SIZE; ++j ) {
                    prices[j] += currentPart.mPrices[j] * currentPart.mKm;
                }
            } else if (from > currentPart.mFrom && to < currentPart.mTo) {
                // whole interval inside block
                for ( int j = 0; j < ALPHABET_SIZE; ++j ) {
                    prices[j] += currentPart.mPrices[j] * (to - from);
                }
                break;
            } else if (from >= currentPart.mFrom && from < currentPart.mTo && to > currentPart.mTo) {
                // start inside or at the start of a block
                for ( int j = 0; j < ALPHABET_SIZE; ++j ) {
                    prices[j] += currentPart.mPrices[j] * (currentPart.mTo - from);
                }
            } else if (to > currentPart.mFrom && to <= currentPart.mTo && from < currentPart.mFrom) {
                // ends inside or the end of a block
                for ( int j = 0; j < ALPHABET_SIZE; ++j ) {
                    prices[j] += currentPart.mPrices[j] * (to - currentPart.mFrom);
                }
            }
        }
    } else {

    }

    printf("%lld - %lld: ", from, to);
    int first = 1;
    for ( int i = 0; i < ALPHABET_SIZE; ++i ) {
        if (prices[i] > 0.0 && first) {
            printf("%c=%lf", i + 65, prices[i]);
            first = 0;
        } else if (prices[i] > 0.0 && !first) {
            printf(", %c=%lf", i + 65, prices[i]);
        }
    }
    printf("\n");
}

int startQuery(SHighway * highway) {
    long long int from, to;
    int check;
    check = scanf("%lld %lld", &from, &to);
    if (check == -1) {
        return 1;
    } else if (check != 2) {
        PRINT_ERROR
        return 2;
    }
    if (from == to || highway->mLength < to || from < 0 || highway->mLength < from) {
        PRINT_ERROR
        return 2;
    }

    calculatePrices(highway, from, to);
    return 0;
}

int main() {
    int retVal;
    SHighway * highway = loadInput();
    if (highway == NULL) {
        return 1;
    }
    printHighway(highway);

    printf("Hledani:\n");
    while ( 1 ) {
        retVal = startQuery(highway);
        if (retVal == 0) {
            continue;
        } else if (retVal == 1) {
            break;
        } else {
            deleteHighway(highway);
            return 1;
        }
    }
    deleteHighway(highway);
    return 0;
}