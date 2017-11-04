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

    int findFourthPoint(double Ax, double Ay, double Bx, double By, double Cx, double Cy, double* solutionX, double* solutionY){
        *solutionX = Bx+(Cx-Ax);
        *solutionY = By+(Cy-Ay);
    }


    int main() {
        double Ax, Ay, Bx, By, Cx, Cy;
        double solution1x, solution1y, solution2x, solution2y, solution3x, solution3y;


        // printf("%.100f\n", 1*10e-100);
        if ( nacti(&Ax, &Ay, &Bx, &By, &Cx, &Cy) != 0){
            return 1;
        }

        if ( (1.0 + DBL_EPSILON) != 1.0 && (1.0 + DBL_EPSILON/2) == 1.0 ){
            printf("epsilon funguje\n");
            printf("%.100f\n",(Ax+Bx)*DBL_EPSILON);
        }

        if ( fabs(Ax * (By - Cy) + Bx * (Cy - Ay) + Cx * (Ay - By) ) < DBL_EPSILON ){
            printf("By-Cy: %.100f\n", By-Cy);
            printf("Cy-Ay: %.100f\n", Cy-Ay);
            printf("Ay-By: %.100f\n", Ay-By);
            printf("Rovnobezniky nelze sestrojit.\n");
            return 1;
        }

        findFourthPoint(Ax, Ay, Bx, By, Cx, Cy, &solution1x, &solution1y);
        findFourthPoint(Bx, By, Cx, Cy, Ax, Ay, &solution2x, &solution2y);
        findFourthPoint(Cx, Cy, Ax, Ay, Bx, By, &solution3x, &solution3y);




        printf("Bod A: [%g, %g]\n", Ax, Ay);
        printf("Bod B: [%g, %g]\n", Bx, By);
        printf("Bod C: [%g, %g]\n", Cx, Cy);

        printf("Solution A: [%g, %g]\n", solution1x, solution1y);
        printf("Solution B: [%g, %g]\n", solution2x, solution2y);
        printf("Solution C: [%g, %g]\n", solution3x, solution3y);

        return 0;
    };