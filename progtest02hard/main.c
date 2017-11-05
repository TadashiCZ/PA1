#include <stdio.h>
#include <float.h>
#include <math.h>



int readSizeOfRoom(long long int* bathroomSideA, long long int* bathroomSideB){
    printf("Minimalni velikost:\n");
    long double inputA, inputB;
    if (scanf("%Lf %Lf", &inputA, &inputB) != 2) return 1;

    if ( ( (inputA*10) - (double) ((long long int) (inputA*10))) > 0 ||
         ( (inputB*10) - (double) ((long long int) (inputB*10))) > 0 ||
         inputA > 10000000 ||
         inputA <= 0 ||
         inputB > 10000000 ||
         inputB <= 0 )

        return 1;
    *bathroomSideA = (long long int) inputA*10;
    *bathroomSideB = (long long int) inputB*10;
    return 0;
}

int validateInput(double tile, double joint){
    if ( ( (tile*10) - (double) ((long long int) (tile*10))) > 0 ||
         ( (joint*10) - (double) ((long long int) (joint*10))) > 0 ||
         tile > 10000000 ||
         tile <= 0 ||
         joint > 10000000 ||
         joint < 0 )

        return 1;

    return 0;
}

long long int greatestCommonDivisor(long long int m, long long int n){
    // printf("GCD: M: %lld, N: %lld.\n", m, n);
    if (n == 0) {
        // printf("Return GCD is %lld.\n", m);
        return m;
    }
    return greatestCommonDivisor(n, m % n);
}

long long int leastCommonMultiple(long long int m, long long int n){
    long long int a = (m*n)/greatestCommonDivisor(m,n);
    // printf("LCD = %lld\n", a);

    return  a;
}


int main() {
    long long int counter = 0, minBathroomSizeA, minBathroomSizeB, tileSize, jointSize, bathroomSizeA, bathroomSizeB, gcd, lcm;
    double inputTile = -1, inputJoint = -1;

    if (readSizeOfRoom(&minBathroomSizeA, &minBathroomSizeB)) {
        printf ( "Nespravny vstup.\n");
        return 1;
    }

    bathroomSizeA = minBathroomSizeA;
    bathroomSizeB = minBathroomSizeB;
    printf("Velikost koupelny je: %.1f x %.1f\n", (double) bathroomSizeA/10, ( (double) bathroomSizeB)/10);
    printf("Dlazdicky:\n");
    while ( scanf("%lf %lf", &inputTile, &inputJoint) == 2 ) {
        if (validateInput(inputTile, inputJoint)){
            printf ( "Nespravny vstup.\n");
            return 1;
        }


        jointSize = (long long int) floor((10*inputJoint)+0.5);
        tileSize = (long long int) floor((10*inputTile)+0.5);

        if (counter == 0){
            //printf("První počítání.\n");
            if (((minBathroomSizeA - jointSize) % (tileSize + jointSize)) != 0) {
                bathroomSizeA = (((minBathroomSizeA - jointSize) / (tileSize + jointSize)) + 1) * (tileSize + jointSize);

            } else {
                bathroomSizeA = ((minBathroomSizeA - jointSize) / (tileSize + jointSize)) * (tileSize + jointSize);
            }
            printf("bathroomSizeA,%lld = (((minBathroomSizeA,%lld - jointSize,%lld) / (tileSize,%lld + jointSize, %lld)) ?+ 1) * (tileSize, %lld + jointSize, %lld\n", bathroomSizeA,minBathroomSizeA,jointSize,tileSize,jointSize,tileSize,jointSize);
            bathroomSizeB = (((minBathroomSizeB - jointSize) % (tileSize + jointSize) != 0 ?
                              ((minBathroomSizeB - jointSize) / (tileSize + jointSize)) + 1 :
                              ((minBathroomSizeB - jointSize) / (tileSize + jointSize))) * (tileSize + jointSize));
            gcd = tileSize+jointSize;
            printf("GCD: %lld\n", gcd);
            lcm = tileSize+jointSize;
            counter++;
            printf("Koupelna má první velikost: %.1f x %.1f\n", ((double) bathroomSizeA)/10, ( (double) bathroomSizeB)/10);
            continue;

        }

        gcd = greatestCommonDivisor(gcd, tileSize+jointSize);
        lcm = leastCommonMultiple(lcm, tileSize+jointSize);
        printf("GCD: %lld\n", gcd);

        bathroomSizeA = ((bathroomSizeA - jointSize) % (lcm)) != 0 ?
                        (((bathroomSizeA - jointSize) / (lcm)) + 1) * (lcm) :
                        ((bathroomSizeA - jointSize) / (lcm)) * (lcm);
        printf("bathroomSizeA,%lld = (((bathroomSizeA,%lld - jointSize,%lld) / (lcm, %lld)) ?+ 1) * (lcm, %lld\n", bathroomSizeA,bathroomSizeA,jointSize,lcm,lcm);
        bathroomSizeB = ( (bathroomSizeB - jointSize) % (lcm) ) != 0 ?
                          (((bathroomSizeB - jointSize) / (lcm)) + 1) * (lcm) :
                          ((bathroomSizeB - jointSize) / (lcm)) * (lcm);
        printf("Koupelna má další velikost: %.1f x %.1f\n", ((double) bathroomSizeA)/10, ( (double) bathroomSizeB)/10);


        counter++;
    }

    if ( feof(stdin) ) {
        if (inputTile == -1 && inputJoint == -1){
            printf("Nespravny vstup.\n");
            return 1;
        }
        printf ("Hotovo, načteno. Velikost koupelny je: %.1f x %.1f\n", (double) bathroomSizeA/10, ( (double) bathroomSizeB)/10);
    } else {
        printf("Nespravny vstup.\n");
        return 1;
    }

    return 0;

}
