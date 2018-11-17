#include <iostream>
#include <cstring>

int same(const char * jedna, const char * dva) {
    if (strlen(jedna) != strlen(dva))return 0;
    for ( int i = 0; i < strlen(jedna); ++i ) {
        if (jedna[i] != dva[strlen(dva) - i]) return 0;
    }

    return 1;

}

int main() {

    const char * name = "aaaa";
    const char * name2 = "aaaa";


    return same(name, name2);
}