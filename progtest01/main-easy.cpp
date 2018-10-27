#include <iostream>
#include <cmath>
#include <cfloat>

int myEqual(double x, double y) {
    return fabs(x - y) <= DBL_EPSILON * (fabs(x) + fabs(y));
}

// source: my code for older Progtest assignment
int areCollinear(double Ax, double Ay, double Bx, double By, double Cx, double Cy) {
   // printf("A: %lf %lf B: %lf %lf C: %lf %lf \n", Ax, Ay, Bx, By, Cx, Cy);
     //printf("prvni %.20lf druha %.20lf\n", ((By-Ay)*(Cx-Bx)), ((Cy-By)*(Bx-Ax))  );
      //printf("fabs %.20lf    eps %.20lf\n", fabs(((By-Ay)*(Cx-Bx)) - ((Cy-By)*(Bx-Ax))), (Ax+Bx)*DBL_EPSILON);

    return (fabs(((By - Ay) * (Cx - Bx)) - ((Cy - By) * (Bx - Ax))) < (Ax + Bx) * DBL_EPSILON * 1000);

}


int readShapes(double * aX, double * aY,
               double * bX, double * bY,
               double * cX, double * cY,
               double * dX, double * dY,
               double * eX, double * eY,
               double * fX, double * fY) {

    printf("Trojuhelnik #1:\nBod A:\n");
    if (scanf("%lf %lf", aX, aY) != 2) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Bod B:\n");
    if (scanf("%lf %lf", bX, bY) != 2) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Bod C:\n");
    if (scanf("%lf %lf", cX, cY) != 2) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    if (areCollinear(*aX, *aY, *bX, *bY, *cX, *cY)) {
        printf("Body netvori trojuhelnik.\n");
        return 1;
    }

    printf("Trojuhelnik #2:\nBod A:\n");
    if (scanf("%lf %lf", dX, dY) != 2) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Bod B:\n");
    if (scanf("%lf %lf", eX, eY) != 2) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Bod C:\n");
    if (scanf("%lf %lf", fX, fY) != 2) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    if (areCollinear(*dX, *dY, *eX, *eY, *fX, *fY)) {
        printf("Body netvori trojuhelnik.\n");
        return 1;
    }

    return 0;
}


int checkCongruentTriangles(double aX, double aY,
                            double bX, double bY,
                            double cX, double cY,
                            double dX, double dY,
                            double eX, double eY,
                            double fX, double fY) {

    double sideA, sideB, sideC, sideD, sideE, sideF;

    sideA = sqrt(pow(fabs(cX - bX), 2) + pow((cY - bY), 2));
    sideB = sqrt(pow(fabs(aX - cX), 2) + pow((aY - cY), 2));
    sideC = sqrt(pow(fabs(aX - bX), 2) + pow((aY - bY), 2));

    sideD = sqrt(pow(fabs(eX - fX), 2) + pow((eY - fY), 2));
    sideE = sqrt(pow(fabs(dX - fX), 2) + pow((dY - fY), 2));
    sideF = sqrt(pow(fabs(dX - eX), 2) + pow((dY - eY), 2));

    if (sideA < sideC)
        std::swap(sideA, sideC);
    if (sideA < sideB)
        std::swap(sideA, sideB);
    if (sideB < sideC)
        std::swap(sideA, sideC);

    if (sideD < sideF)
        std::swap(sideD, sideF);
    if (sideD < sideE)
        std::swap(sideD, sideE);
    if (sideE < sideF)
        std::swap(sideD, sideF);

    if (myEqual(sideA, sideD) && myEqual(sideB, sideE) && myEqual(sideC, sideF)) {
        return 1;
    } else {
        return 0;
    }
}

int checkSameCircumference(double aX, double aY,
                           double bX, double bY,
                           double cX, double cY,
                           double dX, double dY,
                           double eX, double eY,
                           double fX, double fY) {
    double sideA, sideB, sideC, sideD, sideE, sideF;

    sideA = sqrt(pow(fabs(cX - bX), 2) + pow((cY - bY), 2));
    sideB = sqrt(pow(fabs(aX - cX), 2) + pow((aY - cY), 2));
    sideC = sqrt(pow(fabs(aX - bX), 2) + pow((aY - bY), 2));

    sideD = sqrt(pow(fabs(eX - fX), 2) + pow((eY - fY), 2));
    sideE = sqrt(pow(fabs(dX - fX), 2) + pow((dY - fY), 2));
    sideF = sqrt(pow(fabs(dX - eX), 2) + pow((dY - eY), 2));

    if (myEqual((sideA + sideB + sideC), (sideD + sideE + sideF))) {
        return 0;
    } else if ((sideA + sideB + sideC) > (sideD + sideE + sideF)) {
        return 1;
    } else {
        return 2;
    }
}

int main() {
    double aX, aY, bX, bY, cX, cY;
    double dX, dY, eX, eY, fX, fY;
    if (readShapes(&aX, &aY, &bX, &bY, &cX, &cY, &dX, &dY, &eX, &eY, &fX, &fY) == 1) {
        return 1;
    }


    if (checkCongruentTriangles(aX, aY, bX, bY, cX, cY, dX, dY, eX, eY, fX, fY)) {
        printf("Trojuhelniky jsou shodne.\n");
        return 0;
    }

    int circumference = checkSameCircumference(aX, aY, bX, bY, cX, cY, dX, dY, eX, eY, fX, fY);
    if (circumference == 0) {
        printf("Trojuhelniky nejsou shodne, ale maji stejny obvod.\n");
        return 0;
    } else if (circumference == 1) {
        printf("Trojuhelnik #1 ma vetsi obvod.\n");
        return 0;
    } else if (circumference == 2) {
        printf("Trojuhelnik #2 ma vetsi obvod.\n");
        return 0;
    } else {
        return 0;
    }
}
