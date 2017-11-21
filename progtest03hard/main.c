#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#define INVALID_DATE (-1)
#endif /* __PROGTEST__ */
#include <time.h>
#include <memory.h>
#include <stdlib.h>

#define FIRST_FULLMOON 948447054
#define ONE_FULLMOON 2551443
#define TOO_MUCH 7289654401
#define LAST_FULLMOON 7288782909

//help function for convertToEpochTime
int is_leap (int y) {
    return  (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
}

long int convertToEpochTime (int y, int m, int d) {
    long int yday;
    if ( is_leap(y) ) {
        switch (m) {
            case 1:
                yday = d-1;
                break;
            case 2:
                yday = 31 + d-1;
                break;
            case 3:
                yday = 31 + 29 + d-1;
                break;
            case 4:
                yday = 31 + 29 + 31 + d-1;
                break;
            case 5:
                yday = 31 + 29 + 31 + 30 + d-1;
                break;
            case 6:
                yday = 31 + 29 + 31 + 30 + 31 + d-1;
                break;
            case 7:
                yday = 31 + 29 + 31 + 30 + 31 + 30 + d-1;
                break;
            case 8:
                yday = 31 + 29 + 31 + 30 + 31 + 30 + 31 + d-1;
                break;
            case 9:
                yday = 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + d-1;
                break;
            case 10:
                yday = 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + d-1;
                break;
            case 11:
                yday = 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + d-1;
                break;
            case 12:
                yday = 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + d-1;
                break;

        }
    } else {
        switch (m) {
            case 1:
                yday = d-1;
                break;
            case 2:
                yday = 31 + d-1;
                break;
            case 3:
                yday = 31 + 28 + d-1;
                break;
            case 4:
                yday = 31 + 28 + 31 + d-1;
                break;
            case 5:
                yday = 31 + 28 + 31 + 30 + d-1;
                break;
            case 6:
                yday = 31 + 28 + 31 + 30 + 31 + d-1;
                break;
            case 7:
                yday = 31 + 28 + 31 + 30 + 31 + 30 + d-1;
                break;
            case 8:
                yday = 31 + 28 + 31 + 30 + 31 + 30 + 31 + d-1;
                break;
            case 9:
                yday = 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + d-1;
                break;
            case 10:
                yday = 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + d-1;
                break;
            case 11:
                yday = 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + d-1;
                break;
            case 12:
                yday = 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + d-1;
                break;
        }
    }
    return 0 + 0 * 60 + 0 * 3600 + yday * 86400 +
           ((y-1900) - 70) * 31536000 + (((y-1900) - 69) / 4) * 86400 -
           (((y-1900) - 1) / 100) * 86400 + (((y-1900) + 299) / 400) * 86400;

}

long int ClearTimeFromEpochDateTime(long int SecondsSinceEpoch)
{
    long  int sec;
    long  int quadricentennials, centennials, quadrennials, annuals;
    long  int year, leap;
    long int yday;
    long  int month, mday, wday;
    static const  long int daysSinceJan1st[2][13]=
            {
                    {0,31,59,90,120,151,181,212,243,273,304,334,365}, // 365 days, non-leap
                    {0,31,60,91,121,152,182,213,244,274,305,335,366}  // 366 days, leap
            };


    // Re-bias from 1970 to 1601:
    // 1970 - 1601 = 369 = 3*100 + 17*4 + 1 years (incl. 89 leap days) =
    // (3*100*(365+24/100) + 17*4*(365+1/4) + 1*365)*24*3600 seconds
    sec = SecondsSinceEpoch + 11644473600;

    wday = ((sec / 86400 + 1) % 7); // day of week

    // Remove multiples of 400 years (incl. 97 leap days)
    quadricentennials = (sec / 12622780800); // 400*365.2425*24*3600
    sec %= 12622780800;

    // Remove multiples of 100 years (incl. 24 leap days), can't be more than 3
    // (because multiples of 4*100=400 years (incl. leap days) have been removed)
    centennials = (sec / 3155673600); // 100*(365+24/100)*24*3600
    if (centennials > 3)
    {
        centennials = 3;
    }
    sec -= centennials * 3155673600;

    // Remove multiples of 4 years (incl. 1 leap day), can't be more than 24
    // (because multiples of 25*4=100 years (incl. leap days) have been removed)
    quadrennials = (sec / 126230400); // 4*(365+1/4)*24*3600
    if (quadrennials > 24)
    {
        quadrennials = 24;
    }
    sec -= quadrennials * 126230400;

    // Remove multiples of years (incl. 0 leap days), can't be more than 3
    // (because multiples of 4 years (incl. leap days) have been removed)
    annuals = (sec / 31536000); // 365*24*3600
    if (annuals > 3)
    {
        annuals = 3;
    }
    sec -= annuals * 31536000U;

    // Calculate the year and find out if it's leap
    year = 1601 + quadricentennials * 400 + centennials * 100 + quadrennials * 4 + annuals;
    leap = !(year % 4) && (year % 100 || !(year % 400));

    // Calculate the day of the year and the time
    yday = sec / 86400;


    // Calculate the month
    for (mday = month = 1; month < 13; month++)
    {
        if (yday < daysSinceJan1st[leap][month])
        {
            mday += yday - daysSinceJan1st[leap][month - 1];
            break;
        }
    }

    // Fill in C's "struct tm"
    struct tm pTm;
    memset(&pTm, 0, sizeof(pTm));
    pTm.tm_sec = 0;          // [0,59]
    pTm.tm_min = 0;          // [0,59]
    pTm.tm_hour = 0;        // [0,23]
    pTm.tm_mday = (int)mday;        // [1,31]  (day of month)
    pTm.tm_mon = (int)month;    // [0,11]  (month)
    pTm.tm_year = (int)year; // 70+     (year since 1900)
    pTm.tm_wday = (int)wday;        // [0,6]   (day since Sunday AKA day of week)
    pTm.tm_yday = (int)yday;        // [0,365] (day since January 1st AKA day of year)
    pTm.tm_isdst = -1;         // daylight saving time flag

    long int time = convertToEpochTime(pTm.tm_year, pTm.tm_mon, pTm.tm_mday);

    return time;
}
    /* funkce přebraná a upravená z mého loňského kódu */
int checkDate ( int y, int m, int d){
        // check input
    if( y < 2000) return 0;
    if( m < 1 || m > 12) return 0;
    if( d < 1 || d > 31) return 0;

        // check days in February
    if( d>29 && m==2 ) return 0;
        // check leap years
    if ( d==29 && m==2 ){
        if ( y%4000 == 0) return 0;
        else if ( y%400 == 0) return 1;
        else if ( y%100 == 0) return 0;
        else if ( y%4 == 0 ) return 1;
        else { return 0;}
    }
        // check day count for other months
    if (d==31 && !(m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12)) return 0;

    return 1;
}


    //using POSIX formula to convert to Epoch TimeStamp


int isFullMoon ( int y, int m, int d )
{
    if ( !checkDate(y,m,d) ) return INVALID_DATE;

    long int nowDateTime = convertToEpochTime(y,m,d);

    for (long int i = FIRST_FULLMOON ; i <= convertToEpochTime(y,m,d+1) ; i=i+ONE_FULLMOON ){
        long int nowDate = nowDateTime;
        if (nowDate == ClearTimeFromEpochDateTime(i)){
            return 1;
        }
    }
    return 0;
}



// function created by Alexey Frunze and StackOverflow Community
struct tm* SecondsSinceEpochToDateTime(struct tm* pTm, long int SecondsSinceEpoch)
{
    long  int sec;
    long  int quadricentennials, centennials, quadrennials, annuals;
    long int year, leap;
    long  int yday, hour, min;
    long  int month, mday, wday;
    static const long int daysSinceJan1st[2][13]=
            {
                    {0,31,59,90,120,151,181,212,243,273,304,334,365}, // 365 days, non-leap
                    {0,31,60,91,121,152,182,213,244,274,305,335,366}  // 366 days, leap
            };


    // Re-bias from 1970 to 1601:
    // 1970 - 1601 = 369 = 3*100 + 17*4 + 1 years (incl. 89 leap days) =
    // (3*100*(365+24/100) + 17*4*(365+1/4) + 1*365)*24*3600 seconds
    sec = SecondsSinceEpoch + 11644473600;

    wday = ((sec / 86400 + 1) % 7); // day of week

    // Remove multiples of 400 years (incl. 97 leap days)
    quadricentennials = (sec / 12622780800); // 400*365.2425*24*3600
    sec %= 12622780800;

    // Remove multiples of 100 years (incl. 24 leap days), can't be more than 3
    // (because multiples of 4*100=400 years (incl. leap days) have been removed)
    centennials =(sec / 3155673600); // 100*(365+24/100)*24*3600
    if (centennials > 3)
    {
        centennials = 3;
    }
    sec -= centennials * 3155673600;

    // Remove multiples of 4 years (incl. 1 leap day), can't be more than 24
    // (because multiples of 25*4=100 years (incl. leap days) have been removed)
    quadrennials = (sec / 126230400); // 4*(365+1/4)*24*3600
    if (quadrennials > 24)
    {
        quadrennials = 24;
    }
    sec -= quadrennials * 126230400;

    // Remove multiples of years (incl. 0 leap days), can't be more than 3
    // (because multiples of 4 years (incl. leap days) have been removed)
    annuals = (sec / 31536000); // 365*24*3600
    if (annuals > 3)
    {
        annuals = 3;
    }
    sec -= annuals * 31536000;

    // Calculate the year and find out if it's leap
    year = 1601 + quadricentennials * 400 + centennials * 100 + quadrennials * 4 + annuals;
    leap = !(year % 4) && (year % 100 || !(year % 400));

    // Calculate the day of the year and the time
    yday = sec / 86400;
    sec %= 86400;
    hour = sec / 3600;
    sec %= 3600;
    min = sec / 60;
    sec %= 60;

    // Calculate the month
    for (mday = month = 1; month < 13; month++)
    {
        if (yday < daysSinceJan1st[leap][month])
        {
            mday += yday - daysSinceJan1st[leap][month - 1];
            break;
        }
    }

    // Fill in C's "struct tm"
    memset(pTm, 0, sizeof(&pTm));
    pTm->tm_sec = (int)sec;          // [0,59]
    pTm->tm_min = (int)min;          // [0,59]
    pTm->tm_hour = (int)hour;        // [0,23]
    pTm->tm_mday = (int)mday;        // [1,31]  (day of month)
    pTm->tm_mon = (int)month;    // [0,11]  (month)
    pTm->tm_year = (int)year; // 70+     (year since 1900)
    pTm->tm_wday = (int)wday;        // [0,6]   (day since Sunday AKA day of week)
    pTm->tm_yday = (int)yday;        // [0,365] (day since January 1st AKA day of year)
    pTm->tm_isdst = -1;           // daylight saving time flag

    return pTm;
}



int nextFullMoon ( int y, int m, int d,
                   int * nextY, int * nextM, int * nextD )
{
    if ( !checkDate(y,m,d) ) return INVALID_DATE;
    long int nowDateTime = convertToEpochTime(y,m,d);
    if (isFullMoon(y,m,d)) nowDateTime+=ONE_FULLMOON; /*{
        nowDateTime+=ONE_FULLMOON;
        struct tm pTm;
        SecondsSinceEpochToDateTime(&pTm, nowDateTime);
        *nextM = pTm.tm_mon;
        *nextY = pTm.tm_year;
        *nextD = pTm.tm_mday;
        printf ("Y: %d, M: %d, D: %d\n", *nextY, *nextM, *nextD);
        return 1;
    } */
    for (long int i = FIRST_FULLMOON ; i <= TOO_MUCH ; i=i+ONE_FULLMOON ){
        if (i > nowDateTime) {
            struct tm pTm;
            SecondsSinceEpochToDateTime(&pTm, i);
            *nextM = pTm.tm_mon;
            *nextY = pTm.tm_year;
            *nextD = pTm.tm_mday;
          //printf ("Y: %d, M: %d, D: %d\n", *nextY, *nextM, *nextD);
          //  free(&pTm);
            return 1;
        }
    }
    return 0;
}

int prevFullMoon ( int y, int m, int d,
                   int * prevY, int * prevM, int * prevD )
{
    if ( !checkDate(y,m,d) ) return INVALID_DATE;
    long int nowDateTime = labs(convertToEpochTime(y,m,d));
    /*if (isFullMoon(y,m,d)){
        nowDateTime=nowDateTime-ONE_FULLMOON;
        struct tm pTm;
        SecondsSinceEpochToDateTime(&pTm, nowDateTime);
        *prevM = pTm.tm_mon;
        *prevY = pTm.tm_year;
        *prevD = pTm.tm_mday;
        //printf ("Y: %d, M: %d, D: %d\n", *prevY, *prevM, *prevD);
        return 1;
    }*/
    for (long int i = LAST_FULLMOON ; i > FIRST_FULLMOON ; i=i-ONE_FULLMOON ){

        //printf("i: %ld, nowDateTime: %ld\n", i, nowDateTime);
        if (i < nowDateTime) {
            struct tm pTm;
            SecondsSinceEpochToDateTime(&pTm, i);
            *prevM = pTm.tm_mon;
            *prevY = pTm.tm_year;
            *prevD = pTm.tm_mday;
            //printf ("Y: %d, M: %d, D: %d\n", *prevY, *prevM, *prevD);

            return 1;
        }
    }
    printf ("Mimo cyklus Y: %d, M: %d, D: %d\n", *prevY, *prevM, *prevD);
    return 0;

}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] ){
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
  assert ( isFullMoon ( 2017, 1, 12 ) == 1 );
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
  assert ( nextFullMoon ( 2026, 5, 26, &y, &m, &d ) == 1 && y == 2026 && m == 5 && d == 31 );
  assert ( prevFullMoon ( 2037, 5, 21, &y, &m, &d ) == 1 && y == 2037 && m == 4 && d == 29 );
  assert ( prevFullMoon (2025, 7, 10, &y, &m, &d ) == 1 && y == 2025 && m == 6 && d == 11);
  assert ( nextFullMoon ( 2000, 5, 18, &y, &m, &d ) == 1 && y == 2000 && m == 6 && d == 17 );
  assert( nextFullMoon ( 2026, 4, 4, &y, &m, &d ) == 1 && y == 2026 && m == 05 && d == 01);
  assert ( nextFullMoon ( 2000, 5, 18, &y, &m, &d ) == 1 && y == 2000 && m == 6 && d == 17 );




    assert ( prevFullMoon ( 2048, 2, 26, &y, &m, &d ) == 1 && y == 2048 && m == 1 && d == 30);
    assert ( prevFullMoon ( 2100, 10, 17, &y, &m, &d ) == 1 && y == 2100 && m == 9 && d == 18 );
    assert ( prevFullMoon ( 2100, 12, 31, &y, &m, &d ) == 1 && y == 2100 && m == 12 && d == 16);
    assert ( prevFullMoon ( 2000, 2, 18, &y, &m, &d ) == 1 && y == 2000 && m == 1 && d == 21);
    assert ( prevFullMoon ( 2000, 1, 21, &y, &m, &d ) == 1  && y == 1999 && m == 12 && d == 22 );

    return 0;
}
#endif /* __PROGTEST__ */
