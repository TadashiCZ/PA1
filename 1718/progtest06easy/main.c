#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */

char * RLEDecompress ( const char * src )
{
    int max = 100, position = 0;
    char* ret = NULL;
    char toCopy = '\0';
    char number[20];
    int numberInt;
    memset ( number, 0, sizeof number );
    ret = (char*) malloc(max * sizeof(char));

    for (int i = 0 ; src[i] != '\0' ; i++ ){
        if ( position >= max-1 ){
            max += ( max < 1000 ) ? 200 : max / 2;
            ret = (char*) realloc(ret, max * sizeof(char));
        }

        if ( !isdigit(src[i+1]) ) {
           // printf("%c", src[i]);
            //printf("\n");
            ret[position] = src[i];
            position++;
        } else if ( isdigit(src[i+1]) ){
            toCopy = src[i];
            int j=0;
            while( isdigit(src[i+1])){
                number[j] = src[i+1];
                i++;
                j++;
            }
            numberInt = atoi(number);
            //if (numberInt != 0){
                   // printf("Číslo: %d\n", numberInt);
                    max += numberInt;
                    ret = (char*) realloc(ret, max * sizeof(char));
                    for (int k = 0 ; k < numberInt ; k++){
                        ret[position] = toCopy;
                        position++;
                    }
              //  }
            }
            memset ( number, 0, sizeof number );
    }
    ret[position] = '\0';
    printf("Final string: %s\n", ret);
    return ret;
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
            (res = RLEDecompress ( "HH2e6l8o15 35w5o6r-2d0!" )),
            "HHHeeeeeellllllllooooooooooooooo                                   wwwwwoooooor--!" ));
    free ( res );

    assert ( ! strcmp (
            (res = RLEDecompress ( "321a5.6" )),
            "333333333333333333333aaaaa......" ));
    free ( res );

    assert ( ! strcmp (
             (res = RLEDecompress ( "1234" )),
            "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"));
    free ( res );

    assert ( ! strcmp (
            (res = RLEDecompress ( "a1b1c1d1e1f1" )),
            "abcdef"));
    free ( res );

    assert ( ! strcmp (
            (res = RLEDecompress ( "W26CX 54 4BN1 3 22SQ39PI BYI  U LED40M O LX8U2QW9 32G11TGU8B32LHNT 72UYXFP P55MWTJ30 12   TU25 JE GQCE78N77JY59XV  31W  61Y 49F45T35UQHG C30I49I61W45 W4 N  K 69T54TRTH13 77S ZSH20H21C4EP4CL36A15YVW30 22P6I 0F22B 37JF30V3 RDA 3N OK 35K8K4TWEUYI 27KCB66 FUPZX42 SF  AH2OZU H26C37X33 16EEIN D8P1E A9A5ROMHGZ  1NEIMDXT5Y12 57 P 43 D7U FGBR27B J22 1SWT IP36G  29 2U 25Z EMS 5 0 L30EI4T KB7L 26Q6CA SI 6FP  LZN0PLZVRC14 S  YB MBHDW60P0F7QA K 2L SN1AL25SAU0Z V 10MTX D X9IY28Y 13  15 V 63X H11S2QI5ISX33H I HN59O69W0M24A8Z17V  J15A9 0D6D10DYVKRJM 3I  W11N Q  6O T  XRQ 14U23C36 9X B  12 L4S29U17LT11 GL51ES 28 X13 T" )),
            "WWWWWWWWWWWWWWWWWWWWWWWWWWCX                                                          BN                         SQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQPI BYI  U LEDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDM O LXXXXXXXXUUQWWWWWWWWW                                GGGGGGGGGGGTGUUUUUUUUBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBLHNT                                                                        UYXFP PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPMWTJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ               TUUUUUUUUUUUUUUUUUUUUUUUUU JE GQCEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEENNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNJYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYXV                                W                                                              Y                                                 FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTUQHG CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW WWWW N  K                                                                     TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTRTHHHHHHHHHHHHH                                                                             S ZSHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHCCCCEPPPPCLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLAAAAAAAAAAAAAAAYVWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW                      PPPPPPIFFFFFFFFFFFFFFFFFFFFFFB                                     JFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFVVV RDA   N OK                                   KKKKKKKKKKKKTWEUYI                           KCBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB FUPZXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX SF  AHHOZU HHHHHHHHHHHHHHHHHHHHHHHHHHCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX                EEIN DDDDDDDDPE AAAAAAAAAAAAAAROMHGZ  NEIMDXTTTTTYYYYYYYYYYYY                                                          P                                            DDDDDDDU FGBRRRRRRRRRRRRRRRRRRRRRRRRRRRB JJJJJJJJJJJJJJJJJJJJJJ SWT IPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPG                                U                         Z EMS      LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLEIIIIT KBBBBBBBL                          QQQQQQCA SI      FP  LZPLZVRCCCCCCCCCCCCCC S  YB MBHDWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWFFFFFFFQA K  L SNALLLLLLLLLLLLLLLLLLLLLLLLLSAZ V          MTX D XXXXXXXXXIYYYYYYYYYYYYYYYYYYYYYYYYYYYYY                              V                                                               X HHHHHHHHHHHSSQIIIIIISXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXH I HNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOMMMMMMMMMMMMMMMMMMMMMMMMAAAAAAAAZZZZZZZZZZZZZZZZZV  JJJJJJJJJJJJJJJAAAAAAAAADDDDDDDDDDDDDDDDDYVKRJM   I  WWWWWWWWWWWN Q       O T  XRQ              UUUUUUUUUUUUUUUUUUUUUUUCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC         X B              LLLLSSSSSSSSSSSSSSSSSSSSSSSSSSSSSUUUUUUUUUUUUUUUUULTTTTTTTTTTT GLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLES                             XXXXXXXXXXXXX T"));
    free ( res );

    return 0;
}
#endif /* __PROGTEST__ */