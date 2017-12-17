#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */

char * RLEDecompress ( const char * src )
{
    int max = 100;
    char* ret = NULL;

    ret = malloc()
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    char * res;

    assert ( ! strcmp (
            (res = RLEDecompress ( "Hello world!" )),
            "Hello world!" ));
    free ( res );

    assert ( ! strcmp (
            (res = RLEDecompress ( "Hello 30world!" )),
            "Hello                              world!" ));
    free ( res );

    assert ( ! strcmp (
            (res = RLEDecompress ( "Hel2o world!10" )),
            "Hello world!!!!!!!!!!" ));
    free ( res );

    assert ( ! strcmp (
            (res = RLEDecompress ( "H2e6l8o15 35w5o6r-2d0!" )),
            "HHeeeeeellllllllooooooooooooooo                                   wwwwwoooooor--!" ));
    free ( res );

    assert ( ! strcmp (
            (res = RLEDecompress ( "321" )),
            "333333333333333333333" ));
    free ( res );

    return 0;
}
#endif /* __PROGTEST__ */