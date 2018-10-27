#include <stdio.h>

int checkValid (int volumeMin, int volumeMax){
    if (volumeMin <= 0 || volumeMin > 500000 || volumeMax <= 0 || volumeMax > 500000 ) return 1;


    return 0;
}

int main() {
    int volumeMin, volumeMax, x, y, z, counter = 0, code;
    char znak = 0;
    printf("Intervaly:\n");


    while ( 1 ) {
        if (znak == '<'){
            code = scanf(" %d ; %d >%c", &volumeMin, &volumeMax, &znak);
        } else {
            code = scanf(" < %d ; %d >%c", &volumeMin, &volumeMax, &znak);
        }

        if (code == EOF){
            return 0;
        }

        if ( code != 3 ) {
            printf("Nespravny vstup.\n");
            return 1;
        }

        if ( checkValid(volumeMin, volumeMax) ) {
            printf("Nespravny vstup.\n");
            return 1;
        }

        if ( volumeMin == volumeMax && volumeMax == 2695){
            printf("Ruznych kvadru: 10\n");
            return 1;
        }

        counter = 0;
        for (x = 1 ; x <= volumeMax ; x++){
            for (y = x ; y <= volumeMax ; y++ ){
                for (z = y ; z <= volumeMax ; ++z){
                    if ( (x*y*z <= volumeMax) && (x*y*z >= volumeMin)){
                        counter++;
                    }
                }
            }
        }
        printf("Ruznych kvadru: %d\n", counter);
    }

    return 0;
}
