#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TEmployee
{
    struct TEmployee         * m_Next;
    struct TEmployee         * m_Bak;
    char                     * m_Name;
} TEMPLOYEE;

#endif /* __PROGTEST__ */

void printEmployee (TEMPLOYEE * employee){
    printf("Adresa: %p, Jméno: %s, Další: %p, Nadřízený: %p", (void*) employee, employee->m_Name, (void*)employee->m_Next, (void*)employee->m_Bak);
}

TEMPLOYEE        * newEmployee  ( const char      * name,
                                  TEMPLOYEE       * next )
{
    TEMPLOYEE * tmp = (TEMPLOYEE*) malloc(sizeof(TEMPLOYEE));
    tmp->m_Name = (char*) malloc((strlen(name)+1) * sizeof(char));
    strcpy(tmp->m_Name, name);
    tmp->m_Bak  =   NULL;
    tmp->m_Next =   next;
    return tmp;
}

TEMPLOYEE       * copyAfter     ( TEMPLOYEE        * position )
{
    TEMPLOYEE * tmp = (TEMPLOYEE*) malloc(sizeof(TEMPLOYEE));
    tmp->m_Name = (char*) malloc((strlen(position->m_Name)+1) * sizeof(char));
    strcpy(tmp->m_Name, position->m_Name);
    tmp->m_Bak  = position->m_Bak;
    tmp->m_Next = position->m_Next;
    position->m_Next = tmp;
    return tmp;
}

TEMPLOYEE        * cloneList    ( TEMPLOYEE       * src )
{
    TEMPLOYEE * originalHead = src;
    TEMPLOYEE * newHead = src;
    TEMPLOYEE * tmp = src;
    TEMPLOYEE * tmp2 = src;

    if (src == NULL) return NULL;

    while (tmp != NULL){
        copyAfter(tmp);
        tmp = tmp->m_Next->m_Next;
    }
    newHead = originalHead->m_Next;
    tmp = originalHead;
    while (tmp != NULL) {
        if (tmp->m_Bak != NULL) tmp->m_Next->m_Bak = tmp->m_Bak->m_Next;
        tmp = tmp->m_Next->m_Next;
    }

    tmp = originalHead;
    tmp2 = newHead;

    while (tmp != NULL) {
        if (tmp2->m_Next != NULL) tmp2->m_Next = tmp2->m_Next->m_Next;
        if (tmp->m_Next != NULL) tmp->m_Next = tmp->m_Next->m_Next;

        tmp2 = tmp2->m_Next;
        tmp = tmp->m_Next;
    }

    return newHead;
}

void               freeList     ( TEMPLOYEE       * src )
{
    TEMPLOYEE * tmp;
    while ( src != NULL ) {
        tmp = src->m_Next;
        free(src->m_Next);
        free(src->m_Name);
        free(src->m_Bak);
        free(src);
        src = tmp;
    }
}

#ifndef __PROGTEST__
int                main         ( int               argc,
                                  char            * argv [] )
{
    TEMPLOYEE * a, *b;
    char tmp[100];

    assert ( sizeof ( TEMPLOYEE ) == 3 * sizeof ( void * ) );
    a = NULL;
    a = newEmployee ( "Peter", a );
    printEmployee(a);
    a = newEmployee ( "John", a );
    printEmployee(a);
    a = newEmployee ( "Joe", a );
    printEmployee(a);
    a = newEmployee ( "Maria", a );
    printEmployee(a);

    a -> m_Bak = a -> m_Next;
    a -> m_Next -> m_Next -> m_Bak = a -> m_Next -> m_Next -> m_Next;
    a -> m_Next -> m_Next -> m_Next -> m_Bak = a -> m_Next;
    assert ( a
             && ! strcmp ( a -> m_Name, "Maria" )
             && a -> m_Bak == a -> m_Next );
    assert ( a -> m_Next
             && ! strcmp ( a -> m_Next -> m_Name, "Joe" )
             && a -> m_Next -> m_Bak == NULL );
    assert ( a -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "John" )
             && a -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next );
    assert ( a -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
             && a -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next );
    assert ( a -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    
    b = cloneList ( a );
    strncpy ( tmp, "Moe", sizeof ( tmp ) );
    a = newEmployee ( tmp, a );
    strncpy ( tmp, "Victoria", sizeof ( tmp ) );
    a = newEmployee ( tmp, a );
    strncpy ( tmp, "Peter", sizeof ( tmp ) );
    a = newEmployee ( tmp, a );
    b -> m_Next -> m_Next -> m_Next -> m_Bak = b -> m_Next -> m_Next;
    assert ( a
             && ! strcmp ( a -> m_Name, "Peter" )
             && a -> m_Bak == NULL );
    assert ( a -> m_Next
             && ! strcmp ( a -> m_Next -> m_Name, "Victoria" )
             && a -> m_Next -> m_Bak == NULL );
    assert ( a -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "Moe" )
             && a -> m_Next -> m_Next -> m_Bak == NULL );
    assert ( a -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Maria" )
             && a -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next -> m_Next );
    assert ( a -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Joe" )
             && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Bak == NULL );
    assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "John" )
             && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
    assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
             && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next -> m_Next );
    assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    assert ( b
             && ! strcmp ( b -> m_Name, "Maria" )
             && b -> m_Bak == b -> m_Next );
    assert ( b -> m_Next
             && ! strcmp ( b -> m_Next -> m_Name, "Joe" )
             && b -> m_Next -> m_Bak == NULL );
    assert ( b -> m_Next -> m_Next
             && ! strcmp ( b -> m_Next -> m_Next -> m_Name, "John" )
             && b -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next -> m_Next );
    assert ( b -> m_Next -> m_Next -> m_Next
             && ! strcmp ( b -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
             && b -> m_Next -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next );
    assert ( b -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    freeList ( a );
    b -> m_Next -> m_Bak = b -> m_Next;
    a = cloneList ( b );
    assert ( a
             && ! strcmp ( a -> m_Name, "Maria" )
             && a -> m_Bak == a -> m_Next );
    assert ( a -> m_Next
             && ! strcmp ( a -> m_Next -> m_Name, "Joe" )
             && a -> m_Next -> m_Bak == a -> m_Next );
    assert ( a -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "John" )
             && a -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next );
    assert ( a -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
             && a -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next );
    assert ( a -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    assert ( b
             && ! strcmp ( b -> m_Name, "Maria" )
             && b -> m_Bak == b -> m_Next );
    assert ( b -> m_Next
             && ! strcmp ( b -> m_Next -> m_Name, "Joe" )
             && b -> m_Next -> m_Bak == b -> m_Next );
    assert ( b -> m_Next -> m_Next
             && ! strcmp ( b -> m_Next -> m_Next -> m_Name, "John" )
             && b -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next -> m_Next );
    assert ( b -> m_Next -> m_Next -> m_Next
             && ! strcmp ( b -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
             && b -> m_Next -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next );
    assert ( b -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    freeList ( b );
    freeList ( a );
    return 0;
}
#endif /* __PROGTEST__ */
