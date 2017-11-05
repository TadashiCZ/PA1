#include <stdio.h>

int checkValid (int volumeMin, int volumeMax){
    if (volumeMin <= 0 || volumeMin > 500000 || volumeMax <= 0 || volumeMax > 500000 ) return 1;


    return 0;
}

int main() {
    int volumeMin, volumeMax, x, y, z, counter = 0;

    printf("Intervaly:\n");

    while ( scanf("< %d ; %d >", &volumeMin, &volumeMax) == 2 ) {
        if ( checkValid(volumeMin, volumeMax) ) {
            printf("Nespravny vstup.\n");
            return 1;
        }
        counter = 0;
        for (x = 1 ; x <= volumeMax ; x++){
            for (y = 1 ; y <= volumeMax ; y++ ){
                for (z = 1 ; z <= volumeMax ; z++){
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
