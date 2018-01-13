#include <stdio.h>
#include <stdlib.h>

typedef struct region {
    char code;
    long int wage;
    int count;
} TREGION;

int main() {
    long long int averageCount = 0, wageCount = 0;
    double result = 0;
    int inputWage = 0, i;
    char inputCode;
    int checked[26];
    char inputString[81];
    TREGION *pole = (TREGION*) malloc(sizeof(TREGION) * 26);
    char pismenko = 'A';
    for (i = 0; i < 26; i++) {
        pole[i].code = pismenko;
        pole[i].wage = 0;
        pole[i].count = 0;
        checked[i] = 0;
        pismenko++;
    }
    printf("Vstup:\n");
    if (scanf("%c", &pismenko) != 1) {
        printf("Nespravny vstup.\n");
        free(pole);
        return 1;
    }
    if (pismenko != '{') {
        printf("Nespravny vstup.\n");
        free(pole);
        return 1;
    }

    while (scanf(" %d %c %c", &inputWage, &inputCode, &pismenko) == 3) {
        switch (inputCode) {
            case 'A': i = 0; break;
            case 'B': i = 1; break;
            case 'C': i = 2; break;
            case 'D': i = 3; break;
            case 'E': i = 4; break;
            case 'F': i = 5; break;
            case 'G': i = 6; break;
            case 'H': i = 7; break;
            case 'I': i = 8; break;
            case 'J': i = 9; break;
            case 'K': i = 10; break;
            case 'L': i = 11; break;
            case 'M': i = 12; break;
            case 'N': i = 13; break;
            case 'O': i = 14; break;
            case 'P': i = 15; break;
            case 'Q': i = 16; break;
            case 'R': i = 17; break;
            case 'S': i = 18; break;
            case 'T': i = 19; break;
            case 'U': i = 20; break;
            case 'V': i = 21; break;
            case 'W': i = 22; break;
            case 'X': i = 23; break;
            case 'Y': i = 24; break;
            case 'Z': i = 25; break;
            default: i = -1;
        }

        if ((pismenko != ',' && pismenko != '}') || i == -1) {
            printf("Nespravny vstup.\n");
            free(pole);
            return 1;
        }

        pole[i].wage += inputWage;
        pole[i].count++;
        if (pismenko == '}') break;
    }
    fgets(inputString, 81, stdin);
    if ( fgets(inputString, 81, stdin) == inputString){
        printf("Nacitani se povedlo.\n");
    } else {
        printf("Nacitani selhalo.\n");
    }

    if (ferror(stdin)){
        printf("Nespravny vstup.\n");
        free(pole);
        return 1;
    }
    printf("%s", inputString);
    for (int j = 0 ; inputString[j] != '\0'; j++) {
        switch (inputString[j]) {
            case 'A': i = 0; break;
            case 'B': i = 1; break;
            case 'C': i = 2; break;
            case 'D': i = 3; break;
            case 'E': i = 4; break;
            case 'F': i = 5; break;
            case 'G': i = 6; break;
            case 'H': i = 7; break;
            case 'I': i = 8; break;
            case 'J': i = 9; break;
            case 'K': i = 10; break;
            case 'L': i = 11; break;
            case 'M': i = 12; break;
            case 'N': i = 13; break;
            case 'O': i = 14; break;
            case 'P': i = 15; break;
            case 'Q': i = 16; break;
            case 'R': i = 17; break;
            case 'S': i = 18; break;
            case 'T': i = 19; break;
            case 'U': i = 20; break;
            case 'V': i = 21; break;
            case 'W': i = 22; break;
            case 'X': i = 23; break;
            case 'Y': i = 24; break;
            case 'Z': i = 25; break;
            case ' ': i = 30; break;
            case '\n':i = 30; break;
            case EOF: i = 30; break;
            default: i = -1;
        }
        if (i == -1) {
            printf("Nespravny vstup.\n");
            free(pole);
            return 1;
        }

        if (i == 30) {
            if (!averageCount){
                printf("N/A\n");
                continue;
            }
            result = (double)wageCount/(double)averageCount;

            printf("Dělím %lf/%lf.\n", (double)wageCount, (double)averageCount);
            printf("= %lf\n", result);
            averageCount = 0;
            wageCount = 0;
            for (i = 0; i < 26; i++) checked[i]=0;
            continue;
        }

        if (checked[i] == 0) {
            wageCount += pole[i].wage;
            averageCount+=pole[i].count;
            checked[i] = 1;
        }
    }


    for (i = 0; i < 26; i++) {
        printf("%c ", pole[i].code);
        printf("Wage: %ld, ", pole[i].wage);
        printf("Count: %d\n", pole[i].count);
    }

    free(pole);
    return 0;
}
