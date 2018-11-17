#include <iostream>

#define poleX 50
#define poleY 30
#define poleTime 80

const char * brightness = " .:-=+*#%@";

int pole[poleX][poleY][poleTime];


using namespace std;

int drawRectangle(int x, int y, int sizeX, int sizeY, int time) {
    if (x >= poleX || y >= poleY || time >= poleTime) return 1;
    for ( int i = x; i <= x + sizeX; ++i ) {
        for ( int j = y; j <= y + sizeY; ++j ) {
            if (i == x || y == j || i == x + sizeX || j == y + sizeY) {
                pole[i][j][time] = (pole[i][j][time] + 5) % 10;
            }
        }
    }

    return 0;
}

void printCanvas(int time) {
    for ( int i = 0; i < poleX; ++i ) {
        for ( int j = 0; j < poleY; ++j ) {
            printf("%c", brightness[pole[i][j][time]]);
        }
        printf("\n");
    }
}

void deleteCanvas(int time) {
    for ( int i = 0; i < poleX; ++i ) {
        for ( int j = 0; j < poleY; ++j ) {
            pole[i][j][time] = 0;
        }
    }
}

void startCanvas() {
    for ( int i = 0; i < poleX; ++i ) {
        for ( int j = 0; j < poleY; ++j ) {
            for ( int k = 0; k < poleTime; ++k ) {
                pole[i][j][k] = 0;
            }
        }
    }
}

void brightenCanvas(int level, int time) {
    for ( int i = 0; i < poleX; ++i ) {
        for ( int j = 0; j < poleY; ++j ) {
            if (pole[i][j][time] != 0) {
                if ((pole[i][j][time] - level) > 0) pole[i][j][time] = (pole[i][j][time] - level);
                else pole[i][j][time] = 0;
            }
        }
    }
}


void darkenCanvas(int level, int time) {
    for ( int i = 0; i < poleX; ++i ) {
        for ( int j = 0; j < poleY; ++j ) {
            if (pole[i][j][time] != 0) {
                if ((pole[i][j][time] + level) < 9) pole[i][j][time] = (pole[i][j][time] + level);
                else pole[i][j][time] = 9;
            }
        }
    }
}

void moveCanvasRight(int time) {
    for ( int i = 0; i < poleX; ++i ) {
        for ( int j = 0; j < poleY; ++j ) {
            pole[i][j][time] = pole[i][(j + 1) % poleY][time];
        }
    }
}


int main() {
    startCanvas();
    drawRectangle(10, 10, 10, 10, 0);
    printCanvas(0);
    deleteCanvas(0);
    printf("=================");
    printCanvas(0);
    drawRectangle(10, 10, 10, 10, 0);
    drawRectangle(15, 15, 20, 20, 0);
    printf("=================");
    printCanvas(0);
    darkenCanvas(5, 0);
    printf("=================");
    printCanvas(0);
    printf("=================");
    for ( int i = 0; i < 5; ++i ) {
        moveCanvasRight(0);
    }
    printCanvas(0);

    return 0;
}
