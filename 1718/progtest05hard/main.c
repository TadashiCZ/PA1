#include <stdio.h>
#include <stdlib.h>

long long int lcmCalculator(long long int n1, long long int n2){
    long long int gcd=0, lcm, tmp, n1copy, n2copy;
    if (n1 == 1 && n2 == 1){
        return 1;
    } else if (n1 == 1){
        return n2;
    } else if (n2 == 1){
        return n1;
    }
    n1copy = n1;
    n2copy = n2;
    if ( n1 < n2){
        tmp = n1;
        n1 = n2;
        n2 = tmp;
    }
    while (n2 > 0){
        tmp = n1%n2;
        n1 = n2;
        n2 = tmp;
    }
    gcd = n1;
    lcm = (n1copy / gcd)*n2copy;
    return lcm;
}

int checkInput (long long int input){
    if (input <=0) return 1;
    return 0;
}


int checkIndex( long long int index1, long long int index2, long long int n){
    //printf("N je %lld.\n", n);
    if (    index1 > index2 ||
            index1 < 0 ||
            index2 < 0 ||
            index1 > n ||
            index2 > n ||
            index1 == index2){
            //printf("Selhaly indexy.\n");
        return 1;
    }



    return 0;
}

int main() {

long long int max, input, n = 0, index1, index2, result = 1;
long long int* lanes = NULL;
char sign;
int toBreak = 0, res = 0;

    max = 1000;
    lanes = (long long int*) malloc(max * sizeof(long long int));
    printf("Pocty pruhu:\n");
    if ( scanf(" %c", &sign) != 1){
        free(lanes);
        printf("Nespravny vstup.\n");
        return 1;
    } else if (sign != '{') {
        free(lanes);
        printf("Nespravny vstup.\n");
        return 1;
    }

    while ( sign != '}' ){
        if ( scanf ( " %lld %c ", &input, &sign) != 2 ){
            free(lanes);
            printf("Nespravny vstup.\n");
            return 1;
        }
        if (sign == '}') {
            toBreak = 1;
        } else if(sign != ','){
            printf("Nespravny vstup.\n");
            free(lanes);
            return 1;
        }

        if ( n >= max-1 ){
            max += ( max < 10000 ) ? 1000 : max / 2;
            lanes = (long long int*) realloc(lanes, max * sizeof(long long int));
        }

        if (checkInput(input) ){
            free(lanes);
            printf("Nespravny vstup.\n");
            return 1;
        } else {
            lanes[n] = input;
            n++;
            //printf("%lld\n", n);
        }
        if (toBreak){
            break;
        }
    }

    printf("Trasy:\n");
    while ( 1 ) {
        if ( (res = scanf ( " %lld %lld ", &index1, &index2)) != 2 && res!=EOF){
            free(lanes);
            printf("Nespravny vstup.\n");
            return 1;
        } else if (res == EOF){
            break;
        }


        if ( checkIndex(index1, index2, n) ){
            free(lanes);
            printf("Nespravny vstup.\n");
            return 1;
        }
        //printf("Indexy: 1: %lld, 2: %lld\n", index1, index2);
        if (index1 == index2){
            printf("Vozidel: %lld\n", lanes[index1]);
            continue;
        }
        result = lanes[index1];
        for (long long int i = index1 ; i < index2-1 ; i++){
            result = lcmCalculator(result, lanes[i+1]);
           // printf("Mezi výsledek: %lld\n", result);
        }

        printf("Vozidel: %lld\n", result);

    }


    /*printf("Před cyklem | n=%lld, sign='%c'\n", n, sign);
    for (int i = 0 ; i < n ; i++){
        printf("%lld, ", lanes [ i ]);
    }
    printf("\n");*/

    free(lanes);
    return 0;
}
