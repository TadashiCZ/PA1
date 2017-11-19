#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#define INVALID_DATE (-1)
#endif /* __PROGTEST__ */

int isFullMoon ( int y, int m, int d )
{
  /* todo */
}

int prevFullMoon ( int y, int m, int d,
                   int * prevY, int * prevM, int * prevD )
{
  /* todo */
}

int nextFullMoon ( int y, int m, int d,
                   int * nextY, int * nextM, int * nextD )
{
  /* todo */
}
#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  int y, m, d;
  assert ( isFullMoon ( 2000, 7, 16 ) == 1 );
  assert ( isFullMoon ( 2017, 1, 11 ) == 0 );
  assert ( isFullMoon ( 2017, 1, 12 ) == 1 );
  assert ( isFullMoon ( 2017, 1, 13 ) == 0 );
  assert ( isFullMoon ( 2017, 11, 3 ) == 0 );
  assert ( isFullMoon ( 2017, 11, 4 ) == 1 );
  assert ( isFullMoon ( 2017, 11, 5 ) == 0 );
  assert ( isFullMoon ( 2019, 12, 11 ) == 1 );
  assert ( isFullMoon ( 2019, 12, 12 ) == 0 );
  assert ( isFullMoon ( 2019, 12, 13 ) == 0 );
  assert ( prevFullMoon ( 2017, 1, 11, &y, &m, &d ) == 1 && y == 2016 && m == 12 && d == 14 );
  assert ( prevFullMoon ( 2017, 1, 12, &y, &m, &d ) == 1 && y == 2016 && m == 12 && d == 14 );
  assert ( prevFullMoon ( 2017, 1, 13, &y, &m, &d ) == 1 && y == 2017 && m == 1 && d == 12 );
  assert ( prevFullMoon ( 2017, 11, 3, &y, &m, &d ) == 1 && y == 2017 && m == 10 && d == 5 );
  assert ( prevFullMoon ( 2017, 11, 4, &y, &m, &d ) == 1 && y == 2017 && m == 10 && d == 5 );
  assert ( prevFullMoon ( 2017, 11, 5, &y, &m, &d ) == 1 && y == 2017 && m == 11 && d == 4 );
  assert ( prevFullMoon ( 2019, 12, 11, &y, &m, &d ) == 1 && y == 2019 && m == 11 && d == 12 );
  assert ( prevFullMoon ( 2019, 12, 12, &y, &m, &d ) == 1 && y == 2019 && m == 12 && d == 11 );
  assert ( prevFullMoon ( 2019, 12, 13, &y, &m, &d ) == 1 && y == 2019 && m == 12 && d == 11 );
  assert ( nextFullMoon ( 2017, 1, 11, &y, &m, &d ) == 1 && y == 2017 && m == 1 && d == 12 );
  assert ( nextFullMoon ( 2017, 1, 12, &y, &m, &d ) == 1 && y == 2017 && m == 2 && d == 11 );
  assert ( nextFullMoon ( 2017, 1, 13, &y, &m, &d ) == 1 && y == 2017 && m == 2 && d == 11 );
  assert ( nextFullMoon ( 2017, 11, 3, &y, &m, &d ) == 1 && y == 2017 && m == 11 && d == 4 );
  assert ( nextFullMoon ( 2017, 11, 4, &y, &m, &d ) == 1 && y == 2017 && m == 12 && d == 3 );
  assert ( nextFullMoon ( 2017, 11, 5, &y, &m, &d ) == 1 && y == 2017 && m == 12 && d == 3 );
  assert ( nextFullMoon ( 2019, 12, 11, &y, &m, &d ) == 1 && y == 2020 && m == 1 && d == 10 );
  assert ( nextFullMoon ( 2019, 12, 12, &y, &m, &d ) == 1 && y == 2020 && m == 1 && d == 10 );
  assert ( nextFullMoon ( 2019, 12, 13, &y, &m, &d ) == 1 && y == 2020 && m == 1 && d == 10 );
  assert ( isFullMoon ( 2017, 1, 12 ) == 1 );
  assert ( isFullMoon ( 2017, 2, 11 ) == 1 );
  assert ( isFullMoon ( 2017, 3, 12 ) == 1 );
  assert ( isFullMoon ( 2017, 4, 11 ) == 1 );
  assert ( isFullMoon ( 2017, 5, 10 ) == 1 );
  assert ( isFullMoon ( 2017, 6, 9 ) == 1 );
  assert ( isFullMoon ( 2017, 7, 9 ) == 1 );
  assert ( isFullMoon ( 2017, 8, 7 ) == 1 );
  assert ( isFullMoon ( 2017, 9, 6 ) == 1 );
  assert ( isFullMoon ( 2017, 10, 5 ) == 1 );
  assert ( isFullMoon ( 2017, 11, 4 ) == 1 );
  assert ( isFullMoon ( 2017, 12, 3 ) == 1 );
  assert ( isFullMoon ( 2018, 1, 2 ) == 1 );
  assert ( isFullMoon ( 2018, 1, 31 ) == 1 );
  assert ( isFullMoon ( 2018, 3, 2 ) == 1 );
  assert ( isFullMoon ( 2018, 3, 31 ) == 1 );
  assert ( isFullMoon ( 2018, 4, 30 ) == 1 );
  assert ( isFullMoon ( 2018, 5, 29 ) == 1 );
  assert ( isFullMoon ( 2018, 6, 28 ) == 1 );
  assert ( isFullMoon ( 2018, 7, 27 ) == 1 );
  assert ( isFullMoon ( 2018, 8, 26 ) == 1 );
  assert ( isFullMoon ( 2018, 9, 25 ) == 0 );
  assert ( isFullMoon ( 2018, 10, 24 ) == 1 );
  assert ( isFullMoon ( 2018, 11, 23 ) == 1 );
  assert ( isFullMoon ( 2018, 12, 22 ) == 1 );
  assert ( isFullMoon ( 2019, 1, 21 ) == 1 );
  assert ( isFullMoon ( 2019, 2, 19 ) == 1 );
  assert ( isFullMoon ( 2019, 3, 21 ) == 1 );
  assert ( isFullMoon ( 2019, 4, 19 ) == 1 );
  assert ( isFullMoon ( 2019, 5, 18 ) == 0 );
  assert ( isFullMoon ( 2019, 6, 17 ) == 1 );
  assert ( isFullMoon ( 2019, 7, 16 ) == 0 );
  assert ( isFullMoon ( 2019, 8, 15 ) == 1 );
  assert ( isFullMoon ( 2019, 9, 14 ) == 1 );
  assert ( isFullMoon ( 2019, 10, 13 ) == 1 );
  assert ( isFullMoon ( 2019, 11, 12 ) == 1 );
  assert ( isFullMoon ( 2019, 12, 12 ) == 0 );
  assert ( isFullMoon ( 2000, 14, 10 ) == INVALID_DATE );
  assert ( prevFullMoon ( 2000, 11, 31, &y, &m, &d ) == INVALID_DATE );
  assert ( nextFullMoon ( 2001, 2, 29, &y, &m, &d ) == INVALID_DATE );
  assert ( isFullMoon ( 2004, 2, 29 ) == 0 );
  assert ( prevFullMoon ( 2100, 2, 29, &y, &m, &d ) == INVALID_DATE );
  assert ( nextFullMoon ( 2000, 2, 29, &y, &m, &d ) == 1 && y == 2000 && m == 3 && d == 20 );
  return 0;
}
#endif /* __PROGTEST__ */
