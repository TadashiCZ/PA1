#include <stdio.h>
#include <math.h>
#include <float.h>

int nacti ( double* Ax, double* Ay, double* Bx, double* By, double* Cx, double* Cy){
        char c;
        printf("Bod A:\n");

        if (scanf(" %c", &c) != 1) {
            printf("Nespravny vstup.\n");
            return 1;
        } else if (c != '['){
            printf("Nespravny vstup.\n");
            return 1;
        }

        if ( scanf("%lf , %lf", Ax, Ay) != 2 ){
            printf("Nespravny vstup.\n");
            return 1;
        }

        if (scanf(" %c", &c) != 1) {
            printf("Nespravny vstup.\n");
            return 1;
        } else if (c != ']'){
            printf("Nespravny vstup.\n");
            return 1;
        }

        printf("Bod B:\n");

        if (scanf(" %c", &c) != 1) {
            printf("Nespravny vstup.\n");
            return 1;
        } else if (c != '['){
            printf("Nespravny vstup.\n");
            return 1;
        }

        if ( scanf("%lf , %lf", Bx, By) != 2 ){
            printf("Nespravny vstup.\n");
            return 1;
        }

        if (scanf(" %c", &c) != 1) {
            printf("Nespravny vstup.\n");
            return 1;
        } else if (c != ']'){
            printf("Nespravny vstup.\n");
            return 1;
        }

        printf("Bod C:\n");

        if (scanf(" %c", &c) != 1) {
            printf("Nespravny vstup.\n");
            return 1;
        } else if (c != '['){
            printf("Nespravny vstup.\n");
            return 1;
        }

        if ( scanf("%lf , %lf", Cx, Cy) != 2 ){
            printf("Nespravny vstup.\n");
            return 1;
        }

        if (scanf(" %c", &c) != 1) {
            printf("Nespravny vstup.\n");
            return 1;
        } else if (c != ']'){
            printf("Nespravny vstup.\n");
            return 1;
        }

        return 0;
    }

    void findFourthPoint(double Ax, double Ay, double Bx, double By, double Cx, double Cy, double* solutionX, double* solutionY){
        *solutionX = Bx+(Cx-Ax);
        *solutionY = By+(Cy-Ay);
    }

int isSameEnough(double x, double y){
   // if (fabs(x - y) < DBL_EPSILON) return 1;
    double relativeError;
    (fabs(y) > fabs(x)) ? relativeError = fabs((x - y) / y) : relativeError = fabs((x - y) / x);

    if (relativeError <= 0.000000001)

        return 1;

    return 0;
}

int whatShapeItIs(double Ax, double Ay, double Bx, double By, double Cx, double Cy, double Dx, double Dy){
    double sizeOfSide1 = sqrt( pow( fabs(Ax-Bx), 2) + pow( (Ay-By), 2) );
    double sizeOfSide2 = sqrt( pow( fabs(Bx-Cx), 2) + pow( (By-Cy), 2) );
    double sizeOfSide3 = sqrt( pow( fabs(Cx-Dx), 2) + pow( (Cy-Dy), 2) );
    double sizeOfSide4 = sqrt( pow( fabs(Dx-Ax), 2) + pow( (Dy-Ay), 2) );

    double sizeOfDiagonal1 = sqrt( pow( fabs(Ax-Cx), 2) + pow( (Ay-Cy), 2) );
    double sizeOfDiagonal2 = sqrt( pow( fabs(Bx-Dx), 2) + pow( (By-Dy), 2) );

    if (isSameEnough(sizeOfSide1, sizeOfSide2) &&
        isSameEnough(sizeOfSide2, sizeOfSide3) &&
        isSameEnough(sizeOfSide3, sizeOfSide4) &&
        isSameEnough(sizeOfSide4, sizeOfSide1) &&
        isSameEnough(sizeOfSide1, sizeOfSide3) &&
        isSameEnough(sizeOfSide2, sizeOfSide4)){

        if (isSameEnough(sizeOfDiagonal1, sizeOfDiagonal2)) return 1;
        return 2;
    }

    if (isSameEnough(sizeOfSide1, sizeOfSide3) && isSameEnough(sizeOfSide2, sizeOfSide4)){
        if (isSameEnough(sizeOfDiagonal1, sizeOfDiagonal2)) return 3;
        return 4;
    }
/*
    printf("Je AB a BC stejné? %d\n", isSameEnough(sizeOfSide1, sizeOfSide2));
    printf("Je BC a DA stejné? %d\n", isSameEnough(sizeOfSide2, sizeOfSide4));
    printf("Strana A-B: %.10f\n", sizeOfSide1);
    printf("Strana B-C: %.10f\n", sizeOfSide2);
    printf("Strana C-D: %.10f\n", sizeOfSide3);
    printf("Strana D-A: %.10f\n", sizeOfSide4);
    printf("Úhlopříčka A-C: %.10f\n", sizeOfDiagonal1);
    printf("Úhlopříčka B-D: %.10f\n\n", sizeOfDiagonal2);
*/

    return 1;
}


    int main() {
        double Ax, Ay, Bx, By, Cx, Cy;
        double solution1x, solution1y, solution2x, solution2y, solution3x, solution3y;


        // printf("%.100f\n", 1*10e-100);
        if ( nacti(&Ax, &Ay, &Bx, &By, &Cx, &Cy) != 0){
            return 1;
        }

        if ( fabs( Ax * (By - Cy) + Bx * (Cy - Ay) + Cx * (Ay - By) ) < DBL_EPSILON ){
            printf("Rovnobezniky nelze sestrojit.\n");
            return 1;
        }

        findFourthPoint(Ax, Ay, Bx, By, Cx, Cy, &solution1x, &solution1y);
        findFourthPoint(Bx, By, Cx, Cy, Ax, Ay, &solution2x, &solution2y);
        findFourthPoint(Cx, Cy, Ax, Ay, Bx, By, &solution3x, &solution3y);

        printf("A': [%.6g,%.6g], ", solution1x, solution1y);
        switch (whatShapeItIs(Ax,Ay,Bx,By,solution1x,solution1y,Cx,Cy) ){
            case 1: printf("ctverec\n");
                    break;
            case 2: printf("kosoctverec\n");
                    break;
            case 3: printf("obdelnik\n");
                break;
            case 4: printf("rovnobeznik\n");
                break;
        }

        printf("B': [%.6g,%.6g], ", solution2x, solution2y);
        switch(whatShapeItIs(Ax,Ay,Bx,By,Cx,Cy,solution2x,solution2y)) {
            case 1: printf("ctverec\n");
                break;
            case 2: printf("kosoctverec\n");
                break;
            case 3: printf("obdelnik\n");
                break;
            case 4: printf("rovnobeznik\n");
                break;
        }

        printf("C': [%.6g,%.6g], ", solution3x, solution3y);
        switch ( whatShapeItIs(Ax,Ay,solution3x,solution3y,Bx,By,Cx,Cy) ){
            case 1: printf("ctverec\n");
                break;
            case 2: printf("kosoctverec\n");
                break;
            case 3: printf("obdelnik\n");
                break;
            case 4: printf("rovnobeznik\n");
                break;
        }




        // printf("Bod A: [%.10f, %.10f]\n", Ax, Ay);
        // printf("Bod B: [%.10f, %.10f]\n", Bx, By);
        // printf("Bod C: [%.10f, %.10f]\n", Cx, Cy);

        // printf("Solution A: [%.10f, %.10f]\n", solution1x, solution1y);
        // printf("Solution B: [%.10f, %.10f]\n", solution2x, solution2y);
        // printf("Solution C: [%.10f, %.10f]\n", solution3x, solution3y);

        return 0;
    }
