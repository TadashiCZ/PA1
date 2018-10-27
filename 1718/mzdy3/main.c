#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <ctype.h>

typedef struct region {
    char code;
    long int wage;
} TREGION;

int charToString(char inputCode) {
    int i;

    switch (inputCode) {
        case 'A':
            i = 0;
            break;
        case 'B':
            i = 1;
            break;
        case 'C':
            i = 2;
            break;
        case 'D':
            i = 3;
            break;
        case 'E':
            i = 4;
            break;
        case 'F':
            i = 5;
            break;
        case 'G':
            i = 6;
            break;
        case 'H':
            i = 7;
            break;
        case 'I':
            i = 8;
            break;
        case 'J':
            i = 9;
            break;
        case 'K':
            i = 10;
            break;
        case 'L':
            i = 11;
            break;
        case 'M':
            i = 12;
            break;
        case 'N':
            i = 13;
            break;
        case 'O':
            i = 14;
            break;
        case 'P':
            i = 15;
            break;
        case 'Q':
            i = 16;
            break;
        case 'R':
            i = 17;
            break;
        case 'S':
            i = 18;
            break;
        case 'T':
            i = 19;
            break;
        case 'U':
            i = 20;
            break;
        case 'V':
            i = 21;
            break;
        case 'W':
            i = 22;
            break;
        case 'X':
            i = 23;
            break;
        case 'Y':
            i = 24;
            break;
        case 'Z':
            i = 25;
            break;
        default:
            i = -1;
    }

    return i;
}

void cleanChecked(int *checked) {
    for (int i = 0; i < 26; i++) checked[i] = 0;
}

void cleanOutput(TREGION *pole, int count) {
    for (int i = 0; i < count; i++) {
        pole[i].wage = 0;
        pole[i].code = '\0';
    }

}

int main() {
    double result = 0;
    int inputWage = 0, i, max = 100, n = 0, counter = 0, inputCheck;
    char inputCode;
    char inputString[81];
    int checked[26];
    TREGION *pole = (TREGION *) malloc(sizeof(TREGION) * max);
    char inputChar;
    TREGION *output = NULL;

    cleanChecked(checked);

    printf("Vstup:\n");
    if (scanf("%c", &inputChar) != 1) {
        printf("Nespravny vstup.\n");
        free(pole);
        return 1;
    }
    if (inputChar != '{') {
        printf("Nespravny vstup.\n");
        free(pole);
        return 1;
    }

    while (scanf(" %d %c %c", &inputWage, &inputCode, &inputChar) == 3) {
        if (inputChar != ',' && inputChar != '}') {
            printf("Nespravny vstup.\n");
            free(pole);
            return 1;
        }
        printf("Input nr. %d: Region: %c, plat: %d\n", n, inputCode, inputWage);
        pole[n].wage = inputWage;
        pole[n].code = inputCode;
        n++;

        if (inputChar == '}') break;

        if (n >= max - 1) {
            max = (max >= 300) ? max + 100 : max * 2;
            pole = (TREGION *) realloc(pole, sizeof(TREGION) * max);
        }
    }

    output = (TREGION *) malloc(sizeof(TREGION) * n);
    while ((inputCheck = scanf("%s", inputString)) != EOF) {

        if (inputCheck != 1) {
            printf("Nespravny vstup.\n");
            free(pole);
            return 1;
        }

        for (i = 0; (unsigned int) i < strlen(inputString); i++) {
            if (isupper(inputString[i]) && checked[charToString(inputString[i])] == 0) {
                for (int j = 0; j < n; j++) {
                    if (pole[j].code == inputString[i]) {
                        output[counter].code = pole[j].code;
                        output[counter].wage = pole[j].wage;
                        checked[charToString(inputString[i])] = 1;
                        counter++;
                    }
                }
            }
        }

            for (int j = 0; j < counter; j++) {
                printf("Output: Nr. %d, code: %c, wage: %ld\n", j, output[j].code, output[j].wage);
            }
            cleanOutput(output, n);
            cleanChecked(checked);
            counter = 0;
        }

        if (feof(stdin)) {
            free(pole);
            free(output);
            return 1;
        }



    free(pole);
    return 0;
}
