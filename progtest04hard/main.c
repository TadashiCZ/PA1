#include <stdio.h>
#define INVALID_INPUT -1;

void printMap(int pole[2000][2000], int sizeX, int sizeY){
    printf("Výpis cenové mapy:\n");
    for (int i = 0 ; i < sizeY ; i++){
        for ( int j = 0 ; j < sizeX ; j++ ){
            printf(" %d", pole[j][i]);
        }
        printf("\n");
    }
}

int main() {
    int static pole[2000][2000];
    int sizeX, sizeY;
    printf("Velikost mapy:\n");
    if ( scanf(" %d %d", &sizeX, &sizeY) != 2){
        printf("Nespravny vstup.\n");
        return INVALID_INPUT;
    }
    printf("Cenova mapa:\n");
    for (int i = 0 ; i < sizeY ; i++){
        for ( int j = 0 ; j < sizeX ; j++ ){
            if ( scanf(" %d", &pole[j][i]) != 1){
                printf("Nespravny vstup.\n");
                return INVALID_INPUT;
            }
        }
    }

    printMap(pole, sizeX, sizeY);




    return 0;
}
