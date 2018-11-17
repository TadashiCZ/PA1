#include <iostream>

using namespace std;

/*
 * Uloha pro experty
 * lode, vstup x,y na velikost, dynamicka alokace
 * uzivatel zvoli, kam umistit sve lode
 * podle hraci plochy vybrat pocet lodi a typy
 * AI - rozmisti nahodne lode
 * spatny vstup prezije, jen vynada
 * uzivatel zada souradnice, kam strili, dostane odpoved
 * AI - strili nahodne (za vic Plus je to pokud bude mene nahodne)
 */

class CMap {
public:
    int mX, mY;
    int ** mMap;

    CMap(int x, int y) : mY(y), mX(x) {
        mMap = new int * [x];
        for ( int i = 0; i < y; ++i ) {
            mMap[i] = new int[y];
        }
    }

    ~CMap() {
        delete[] mMap;
    }

};


CMap * readInput() {
    int x, y;
    char c;
    cout << "Zadej velikost mapy x, pak y" << endl;
    cin >> x >> c >> y;
    CMap * mapa = new CMap(x, y);

    if (mapa->mX * mapa->mY < 10) {
        cout << "Mala mapa, ale dobre" << endl;
        bool ok = false;
        for ( int i = 0; i < 3; ++i ) {
            while ( !ok ) {
                cout << "Kam chces dat lod cislo " << i << " o velikosti 1? Zadej x, y" << endl;
                cin >> x >> c >> y;
                if (cin.good()) {
                    ok = true;
                }
            }
            mapa->mMap[x][y] = 1;
        }
    } else {
        for ( int i = 0; i < 3; ++i ) {
            bool ok = false;
            while ( !ok ) {
                cout << "Kam chces dat predek lodi cislo " << i << " o velikosti 2? Zadej x, y" << endl;
                cin >> x >> c >> y;
                if (cin.good() && x < mapa->mX && y < mapa->mY) {
                    ok = true;
                }
            }
            int x2 = -1, y2 = -1;
            ok = false;
            while ( !ok ) {
                cout << "Kam chces dat zadek lodi cislo " << i << " o velikosti 2? Zadej x, y" << endl;
                cin >> x2 >> c >> y2;
                if (cin.good() && ( x-x2 > 1 || y-y2 > 1) && !(y-y2==1&&x-x2==1) && x < mapa->mX && y < mapa->mY) {
                    ok = true;
                }
            }
            mapa->mMap[x][y] = i;
            mapa->mMap[x2][y2] = i;
        }
    }


    return mapa;
}

int main() {
    CMap * mapa = readInput();


    return 0;
}