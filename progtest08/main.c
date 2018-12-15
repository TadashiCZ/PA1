#ifndef __PROGTEST__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TCar {
	struct TCar * m_Next;
	char * m_Model;
} TCAR;

typedef struct TEmployee {
	struct TEmployee * m_Next;
	struct TCar * m_Car;
	char * m_Name;
} TEMPLOYEE;

typedef struct TOffice {
	TEMPLOYEE * m_Emp;
	TCAR * m_Car;
} TOFFICE;

#endif /* __PROGTEST__ */

// kód návrhově vychází z mého loňského kódu pro úlohu 8

TOFFICE * initOffice() {
	TOFFICE * tmp = ( TOFFICE * ) malloc( sizeof( TOFFICE ) );
	tmp->m_Emp = NULL;
	tmp->m_Car = NULL;
	return tmp;
}

void addEmployee(TOFFICE * office,
                 const char * name) {
	TEMPLOYEE * newEmployee = ( TEMPLOYEE * ) malloc( sizeof( TEMPLOYEE ) );
	newEmployee->m_Car = NULL;
	newEmployee->m_Next = NULL;
	newEmployee->m_Name = ( char * ) malloc( ( strlen( name ) + 1 ) * sizeof( char ) );
	strcpy( newEmployee->m_Name, name );
	if ( office->m_Emp == NULL ) {
		office->m_Emp = newEmployee;
	} else {
		newEmployee->m_Next = office->m_Emp;
		office->m_Emp = newEmployee;
	}
}

void addCar(TOFFICE * office,
            const char * model) {
	TCAR * newCar = ( TCAR * ) malloc( sizeof( TCAR ) );
	newCar->m_Next = NULL;
	newCar->m_Model = ( char * ) malloc( strlen( model ) + 1 * sizeof( char ) );
	strcpy( newCar->m_Model, model );
	if ( office->m_Car == NULL ) {
		office->m_Car = newCar;
	} else {
		newCar->m_Next = office->m_Car;
		office->m_Car = newCar;
	}
}

TEMPLOYEE * copyEmpAfter(TEMPLOYEE * position) {
	TEMPLOYEE * tmp = ( TEMPLOYEE * ) malloc( sizeof( TEMPLOYEE ) );
	tmp->m_Name = ( char * ) malloc( ( strlen( position->m_Name ) + 1 ) * sizeof( char ) );
	strcpy( tmp->m_Name, position->m_Name );
	tmp->m_Car = position->m_Car;
	tmp->m_Next = position->m_Next;
	position->m_Next = tmp;
	return tmp;
}

TCAR * copyCarAfter(TCAR * position) {
	TCAR * tmp = ( TCAR * ) malloc( sizeof( TCAR ) );
	tmp->m_Model = ( char * ) malloc( ( strlen( position->m_Model ) + 1 ) * sizeof( char ) );
	strcpy( tmp->m_Model, position->m_Model );
	tmp->m_Next = position->m_Next;
	position->m_Next = tmp;
	return tmp;
}

TOFFICE * cloneOffice(TOFFICE * office) {
	if ( office == NULL ) return NULL;

	TEMPLOYEE * origEmpHead = office->m_Emp;
	TEMPLOYEE * newEmpHead = NULL;
	TCAR * origCarHead = office->m_Car;
	TCAR * newCarHead = NULL;
	TEMPLOYEE * tmpEmp = office->m_Emp;
	TEMPLOYEE * tmpEmp2 = NULL;
	TCAR * tmpCar = office->m_Car;
	TCAR * tmpCar2 = NULL;

	if ( office->m_Car == NULL && office->m_Emp == NULL ) {
		TOFFICE * newOffice = ( TOFFICE * ) malloc( sizeof( TOFFICE ) );
		newOffice->m_Emp = NULL;
		newOffice->m_Car = NULL;
		return newOffice;
	}

	if (office->m_Emp != NULL && office->m_Car == NULL){
		while ( tmpEmp != NULL ) {
			copyEmpAfter( tmpEmp );
			tmpEmp = tmpEmp->m_Next->m_Next;
		}
		newEmpHead = origEmpHead->m_Next;
		tmpEmp = origEmpHead;
		tmpEmp2 = newEmpHead;

		while ( tmpEmp != NULL ) {
			if ( tmpEmp->m_Next != NULL ) {
				tmpEmp->m_Next = tmpEmp->m_Next->m_Next;
			} else {
				tmpEmp->m_Next = NULL;
			}

			if ( tmpEmp2->m_Next != NULL ) {
				tmpEmp2->m_Next = tmpEmp2->m_Next->m_Next;
			} else {
				tmpEmp2->m_Next = NULL;
			}

			tmpEmp2 = tmpEmp2->m_Next;
			tmpEmp = tmpEmp->m_Next;
		}

		TOFFICE * newOffice = ( TOFFICE * ) malloc( sizeof( TOFFICE ) );
		newOffice->m_Car = NULL;
		newOffice->m_Emp = newEmpHead;
		return newOffice;
	}

	if (office->m_Emp == NULL && office->m_Car != NULL){
		while ( tmpCar != NULL ) {
			copyCarAfter( tmpCar );
			tmpCar = tmpCar->m_Next->m_Next;
		}

		newCarHead = origCarHead->m_Next;
		tmpCar = origCarHead;
		tmpCar2 = newCarHead;

		while ( tmpCar != NULL ) {
			if ( tmpCar->m_Next != NULL ) {
				tmpCar->m_Next = tmpCar->m_Next->m_Next;
			} else {
				tmpCar->m_Next = NULL;
			}

			if ( tmpCar2->m_Next != NULL ) {
				tmpCar2->m_Next = tmpCar2->m_Next->m_Next;
			} else {
				tmpCar2->m_Next = NULL;
			}

			tmpCar2 = tmpCar2->m_Next;
			tmpCar = tmpCar->m_Next;
		}

		TOFFICE * newOffice = ( TOFFICE * ) malloc( sizeof( TOFFICE ) );
		newOffice->m_Car = newCarHead;
		newOffice->m_Emp = NULL;
		return newOffice;
	}

	while ( tmpEmp != NULL ) {
		copyEmpAfter( tmpEmp );
		tmpEmp = tmpEmp->m_Next->m_Next;
	}

	while ( tmpCar != NULL ) {
		copyCarAfter( tmpCar );
		tmpCar = tmpCar->m_Next->m_Next;
	}

	newEmpHead = origEmpHead->m_Next;
	tmpEmp = origEmpHead;

	while ( tmpEmp != NULL ) {
		if ( tmpEmp->m_Car != NULL ) tmpEmp->m_Next->m_Car = tmpEmp->m_Car->m_Next;
		tmpEmp = tmpEmp->m_Next->m_Next;
	}

	tmpEmp = origEmpHead;
	tmpEmp2 = newEmpHead;

	while ( tmpEmp != NULL ) {
		if ( tmpEmp->m_Next != NULL ) {
			tmpEmp->m_Next = tmpEmp->m_Next->m_Next;
		} else {
			tmpEmp->m_Next = NULL;
		}

		if ( tmpEmp2->m_Next != NULL ) {
			tmpEmp2->m_Next = tmpEmp2->m_Next->m_Next;
		} else {
			tmpEmp2->m_Next = NULL;
		}

		tmpEmp2 = tmpEmp2->m_Next;
		tmpEmp = tmpEmp->m_Next;
	}

	newCarHead = origCarHead->m_Next;
	tmpCar = origCarHead;
	tmpCar2 = newCarHead;

	while ( tmpCar != NULL ) {
		if ( tmpCar->m_Next != NULL ) {
			tmpCar->m_Next = tmpCar->m_Next->m_Next;
		} else {
			tmpCar->m_Next = NULL;
		}

		if ( tmpCar2->m_Next != NULL ) {
			tmpCar2->m_Next = tmpCar2->m_Next->m_Next;
		} else {
			tmpCar2->m_Next = NULL;
		}

		tmpCar2 = tmpCar2->m_Next;
		tmpCar = tmpCar->m_Next;
	}

	TOFFICE * newOffice = ( TOFFICE * ) malloc( sizeof( TOFFICE ) );
	newOffice->m_Car = newCarHead;
	newOffice->m_Emp = newEmpHead;
	return newOffice;
}

void freeOffice(TOFFICE * office) {

	TEMPLOYEE * tmpEmp;
	while ( office->m_Emp != NULL ) {
		tmpEmp = office->m_Emp->m_Next;
		free( office->m_Emp->m_Name );
		free( office->m_Emp );
		office->m_Emp = tmpEmp;
	}

	TCAR * tmpCar;
	while ( office->m_Car != NULL ) {
		tmpCar = office->m_Car->m_Next;
		free( office->m_Car->m_Model );
		free( office->m_Car );
		office->m_Car = tmpCar;
	}
	free( office );
}

#ifndef __PROGTEST__

int main(int argc, char * argv[]) {
	TOFFICE * a, * b;
	char tmp[100];

	assert ( sizeof( TOFFICE ) == 2 * sizeof( void * ) );
	assert ( sizeof( TEMPLOYEE ) == 3 * sizeof( void * ) );
	assert ( sizeof( TCAR ) == 2 * sizeof( void * ) );
	a = initOffice();
	addEmployee( a, "Peter" );
	addEmployee( a, "John" );
	addEmployee( a, "Joe" );
	addEmployee( a, "Maria" );
	addCar( a, "Skoda Octavia" );
	addCar( a, "VW Golf" );
	a->m_Emp->m_Car = a->m_Car;
	a->m_Emp->m_Next->m_Next->m_Car = a->m_Car->m_Next;
	a->m_Emp->m_Next->m_Next->m_Next->m_Car = a->m_Car;
	assert ( a->m_Emp
	         && !strcmp( a->m_Emp->m_Name, "Maria" )
	         && a->m_Emp->m_Car == a->m_Car );
	assert ( a->m_Emp->m_Next
	         && !strcmp( a->m_Emp->m_Next->m_Name, "Joe" )
	         && a->m_Emp->m_Next->m_Car == NULL );
	assert ( a->m_Emp->m_Next->m_Next
	         && !strcmp( a->m_Emp->m_Next->m_Next->m_Name, "John" )
	         && a->m_Emp->m_Next->m_Next->m_Car == a->m_Car->m_Next );
	assert ( a->m_Emp->m_Next->m_Next->m_Next
	         && !strcmp( a->m_Emp->m_Next->m_Next->m_Next->m_Name, "Peter" )
	         && a->m_Emp->m_Next->m_Next->m_Next->m_Car == a->m_Car );
	assert ( a->m_Emp->m_Next->m_Next->m_Next->m_Next == NULL );
	assert ( a->m_Car
	         && !strcmp( a->m_Car->m_Model, "VW Golf" ) );
	assert ( a->m_Car->m_Next
	         && !strcmp( a->m_Car->m_Next->m_Model, "Skoda Octavia" ) );
	assert ( a->m_Car->m_Next->m_Next == NULL );

	b = cloneOffice( a );
	strncpy( tmp, "Moe", sizeof( tmp ) );
	addEmployee( a, tmp );
	strncpy( tmp, "Victoria", sizeof( tmp ) );
	addEmployee( a, tmp );
	strncpy( tmp, "Peter", sizeof( tmp ) );
	addEmployee( a, tmp );
	strncpy( tmp, "Citroen C4", sizeof( tmp ) );
	addCar( a, tmp );
	b->m_Emp->m_Next->m_Next->m_Next->m_Car = b->m_Car->m_Next->m_Next;
	assert ( a->m_Emp
	         && !strcmp( a->m_Emp->m_Name, "Peter" )
	         && a->m_Emp->m_Car == NULL );
	assert ( a->m_Emp->m_Next
	         && !strcmp( a->m_Emp->m_Next->m_Name, "Victoria" )
	         && a->m_Emp->m_Next->m_Car == NULL );
	assert ( a->m_Emp->m_Next->m_Next
	         && !strcmp( a->m_Emp->m_Next->m_Next->m_Name, "Moe" )
	         && a->m_Emp->m_Next->m_Next->m_Car == NULL );
	assert ( a->m_Emp->m_Next->m_Next->m_Next
	         && !strcmp( a->m_Emp->m_Next->m_Next->m_Next->m_Name, "Maria" )
	         && a->m_Emp->m_Next->m_Next->m_Next->m_Car == a->m_Car->m_Next );
	assert ( a->m_Emp->m_Next->m_Next->m_Next->m_Next
	         && !strcmp( a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Name, "Joe" )
	         && a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Car == NULL );
	assert ( a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next
	         && !strcmp( a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "John" )
	         && a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Car == a->m_Car->m_Next->m_Next );
	assert ( a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next
	         && !strcmp( a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "Peter" )
	         && a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Car == a->m_Car->m_Next );
	assert ( a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL );
	assert ( a->m_Car
	         && !strcmp( a->m_Car->m_Model, "Citroen C4" ) );
	assert ( a->m_Car->m_Next
	         && !strcmp( a->m_Car->m_Next->m_Model, "VW Golf" ) );
	assert ( a->m_Car->m_Next->m_Next
	         && !strcmp( a->m_Car->m_Next->m_Next->m_Model, "Skoda Octavia" ) );
	assert ( a->m_Car->m_Next->m_Next->m_Next == NULL );
	assert ( b->m_Emp
	         && !strcmp( b->m_Emp->m_Name, "Maria" )
	         && b->m_Emp->m_Car == b->m_Car );
	assert ( b->m_Emp->m_Next
	         && !strcmp( b->m_Emp->m_Next->m_Name, "Joe" )
	         && b->m_Emp->m_Next->m_Car == NULL );
	assert ( b->m_Emp->m_Next->m_Next
	         && !strcmp( b->m_Emp->m_Next->m_Next->m_Name, "John" )
	         && b->m_Emp->m_Next->m_Next->m_Car == b->m_Car->m_Next );
	assert ( b->m_Emp->m_Next->m_Next->m_Next
	         && !strcmp( b->m_Emp->m_Next->m_Next->m_Next->m_Name, "Peter" )
	         && b->m_Emp->m_Next->m_Next->m_Next->m_Car == NULL );
	assert ( b->m_Emp->m_Next->m_Next->m_Next->m_Next == NULL );
	assert ( b->m_Car
	         && !strcmp( b->m_Car->m_Model, "VW Golf" ) );
	assert ( b->m_Car->m_Next
	         && !strcmp( b->m_Car->m_Next->m_Model, "Skoda Octavia" ) );
	assert ( b->m_Car->m_Next->m_Next == NULL );

	freeOffice( a );
	freeOffice( b );
	return 0;
}

#endif /* __PROGTEST__ */