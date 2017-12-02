#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void copyMap (int input[2000][2000], int newMap[2000][2000], int sizeX, int sizeY){
    for (int i = 0 ; i < sizeY ; i++){
        for ( int j = 0 ; j < sizeX ; j++ ) {
            newMap[j][i] = input[j][i];
        }
    }
}

void countMap (int map[2000][2000], int sizeX, int sizeY){
    for (int i = 0 ; i < sizeY ; i++){
        int sum = 0;
        for ( int j = 0 ; j < sizeX ; j++ ) {
            sum+=map[j][i];
            map[j][i]=sum;
        }
    }

    for (int j = 0 ; j < sizeX ; j++){
        int sum = 0;
        for ( int i = 0 ; i < sizeY ; i++ ) {
            sum+=map[j][i];
            map[j][i]=sum;
        }
    }

}

int readMap (int map[2000][2000], int sizeX, int sizeY){
    for (int i = 0 ; i < sizeY ; i++){
        for ( int j = 0 ; j < sizeX ; j++ ){
            if ( scanf(" %d ", &map[j][i]) != 1){
                printf("Nespravny vstup.\n");
                return 0;
            }
        }
    }
    return 1;
}


int main() {
    const char *low_alpha = "qwertyuiopasdfghjklzxcvbnm";

    int static countedMap[2000][2000];
    int static map[2000][2000];
    int sizeX, sizeY, partSize = 0;
    long int maxPrice = 0;
    char input[20], cutInput[20];
    char *ptr;
    printf("Velikost mapy:\n");

    if ( scanf(" %d %d", &sizeX, &sizeY) != 2){
        printf("Nespravny vstup.\n");
        return INVALID_INPUT;
    }

    printf("Cenova mapa:\n");
    if ( !readMap(map, sizeX, sizeY) ) return INVALID_INPUT;

    copyMap(map, countedMap, sizeX, sizeY);
    countMap(countedMap, sizeX, sizeY);



    printMap(map, sizeX, sizeY);
    printf("----\n");
     printMap(countedMap, sizeX, sizeY);


    printf("Dotazy:\n");

    //while ( fgets(input, 20, stdin) != NULL ){
    while ( scanf(" %s %ld ", input, &maxPrice) == 2 ){
        //size_t integer_start = strspn(input, low_alpha);
        //maxPrice = strtol(&input[integer_start], &ptr, 10);
        // strncpy(cutInput, input, integer_start);
        printf("%s | maxPrice = %ld\n", input, maxPrice);

        for (int i = 0 ; i < sizeY ; i++){
            for ( int j = 0 ; j < sizeX ; j++ ) {
                if (countedMap[j][i] < maxPrice && j*i >= partSize) {
                   // printf("Pozice %d, %d.\n", j, i);
                    partSize = j*i;
                }
            }
        }





    }




    return 0;
}
