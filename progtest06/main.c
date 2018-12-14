#include <stdio.h>
#include <stdlib.h>

typedef struct grid {
	char ** mGrid;
	int ** mStripGrid;
	int mHasStrip;
	int mSizeX;
	int mCountX;
	int mSizeY;
	int mCountY;
} SGrid;

void deleteGrid(SGrid * grid) {
	for ( int i = 0 ; i < grid->mCountY ; ++i ) {
		free( grid->mGrid[i] );
	}
	free( grid->mGrid );
	if ( grid->mHasStrip ) {
		for ( int i = 0 ; i < grid->mCountY ; ++i ) {
			free( grid->mStripGrid[i] );
		}
		free( grid->mStripGrid );

	}
	free( grid );
}

int loadFirstLine(SGrid * grid) {
	printf( "Zadejte osmismerku:\n" );
	char c;
	while ( 1 ) {
		if ( scanf( "%c", &c ) == EOF ) {
			return 1;
		}
		if ( c != '\n' && c != '.' && ( c > 122 || c < 97 ) ) {
			return -1;
		}

		if ( c == '\n' ) {
			break;
		}
		grid->mGrid[grid->mCountY][grid->mCountX] = c;
		grid->mCountX++;
		if ( grid->mCountX >= grid->mSizeX ) {
			grid->mSizeX *= 2;
			grid->mGrid[grid->mCountY] = ( char * ) realloc( grid->mGrid[grid->mCountY], grid->mSizeX * sizeof( char ) );
		}
	}

	grid->mSizeX = grid->mCountX;
	grid->mGrid[grid->mCountY] = ( char * ) realloc( grid->mGrid[grid->mCountY], grid->mSizeX * sizeof( char ) );
	grid->mCountY++;
	return grid->mCountX;
}

int loadLine(SGrid * grid) {
	char c;
	int counter = 0;
	int first = 1;
	grid->mGrid[grid->mCountY] = ( char * ) malloc( grid->mCountX * sizeof( char ) );
	while ( 1 ) {
		if ( scanf( "%c", &c ) == EOF ) {
			free( grid->mGrid[grid->mCountY] );
			return -1;
		}

		if ( c != '\n' && c != 46 && ( c > 122 || c < 97 ) ) {
			free( grid->mGrid[grid->mCountY] );
			return -1;
		}

		if ( c == '\n' ) {
			if ( !first ) break;
			free( grid->mGrid[grid->mCountY] );
			return 1;
		}

		grid->mGrid[grid->mCountY][counter] = c;
		counter++;
		first = 0;
		if ( counter > grid->mCountX ) {
			return -1;
		}

		if ( counter > grid->mSizeX ) {
			grid->mSizeX *= 2;
			grid->mGrid[grid->mCountY] = ( char * ) realloc( grid->mGrid[grid->mCountY], grid->mSizeX * sizeof( char ) );
		}
	}

	if ( counter != grid->mCountX ) {
		return -1;
	}

	grid->mCountY++;
	return 0;
}

int loadMap(SGrid * grid) {
	grid->mSizeY = 2;
	grid->mCountY = 0;
	grid->mCountX = 0;
	grid->mGrid = ( char ** ) malloc( grid->mSizeY * sizeof( char * ) );
	grid->mSizeX = 10;
	grid->mGrid[0] = ( char * ) malloc( grid->mSizeX * sizeof( char ) );


	int lineSize = loadFirstLine( grid );

	if ( lineSize == -1 ) {
		return 1;
	}

	while ( 1 ) {
		int ret = loadLine( grid );
		if ( ret == -1 ) {
			return 1;
		} else if ( ret == 1 ) {
			break;
		}

		if ( grid->mCountY >= grid->mSizeY ) {
			grid->mSizeY *= 2;
			grid->mGrid = ( char ** ) realloc( grid->mGrid, grid->mSizeY * sizeof( char * ) );
		}
	}


	grid->mSizeY = grid->mCountY;
	grid->mGrid = ( char ** ) realloc( grid->mGrid, grid->mSizeY * sizeof( char * ) );

	grid->mStripGrid = ( int ** ) malloc( grid->mCountY * sizeof( int * ) );
	for ( int i = 0 ; i < grid->mCountY ; ++i ) {
		grid->mStripGrid[i] = ( int * ) malloc( grid->mCountX * sizeof( int ) );
	}
	grid->mHasStrip = 1;

	return 0;
}

void printSelection(SGrid * pGrid) {
	printf( "Vysledek:\n" );
	for ( int i = 0 ; i < pGrid->mCountY ; ++i ) {
		for ( int j = 0 ; j < pGrid->mCountX ; ++j ) {
			if ( pGrid->mStripGrid[i][j] == 0 ) {
				printf( "%c", pGrid->mGrid[i][j] );
			}
		}
	}
	printf( "\n" );
}

void printGridInfo(SGrid * grid) {
	printf( "Grid:\n" );
	printf( "SizeY: %d, SizeX: %d, CountY: %d, CountX: %d, hasStrip: %d\n", grid->mSizeY, grid->mSizeX, grid->mCountY,
	        grid->mCountX, grid->mHasStrip );

	for ( int i = 0 ; i < grid->mCountY ; ++i ) {
		for ( int j = 0 ; j < grid->mCountX ; ++j ) {
			printf( "%c", grid->mGrid[i][j] );
		}
		printf( "\n" );
	}
	if ( grid->mHasStrip ) {
		printf( "\n" );
		for ( int i = 0 ; i < grid->mCountY ; ++i ) {
			for ( int j = 0 ; j < grid->mCountX ; ++j ) {
				printf( "%d", grid->mStripGrid[i][j] );
			}
			printf( "\n" );
		}
	}
	printf( "\n\n" );


}

int tryNorth(SGrid * pGrid, const char * input, int inputSize, int startI, int startJ) {
	int i = startI, j = startJ;
	int k = 0, found = 0;
	//printGridInfo( pGrid );
	while ( input[k] == pGrid->mGrid[i][j] ) {
		//printf( "input: %c, grid: %c, posY: %d, posX: %d, k: %d, inputS: %d\n", input[k], pGrid->mGrid[i][j], i, j, k , inputSize-1);
		k++;
		if ( k >= inputSize-1 ) {
			found = 1;
			break;
		}
		i--;
		if ( i < 0 ) {
			break;
		}
	}

	if ( found ) {
		for ( int l = k ; l > 0 ; --l ) {
			pGrid->mStripGrid[i][j] = 1;
			i++;
		}
		return 1;
	}

	return 0;
}

int searchForInput(SGrid * pGrid, char * input, int inputSize) {
	int found = 0;

	printf( "Searching for: %s - ", input );

	for ( int i = 0 ; i < pGrid->mCountY ; ++i ) {
		for ( int j = 0 ; j < pGrid->mCountX ; ++j ) {
			if ( tryNorth( pGrid, input, inputSize, i, j ) == 1 ) {
				printf("Found\n");
				found = 1;
			}
			// todo tryNorthWest
			// todo tryWest
			// todo trySouthWest
			// todo trySouth
			// todo trySouthEast
			// todo tryEast
			// todo tryNorthEast
		}
	}

	if ( found == 0 ) {
		return 0;
	}

	//printGridInfo(pGrid);
	return 1;
}

int readQuery(SGrid * grid) {
	char * input, c = '.';
	int inputSize = 20, inputCount = 0, lastInput = 0;
	input = ( char * ) malloc( inputSize * sizeof( char ) );

	while ( 1 ) {
		if ( scanf( "%c", &c ) == EOF ) {
			input[inputCount++] = '\0';
			lastInput = 1;
			break;
		}
		if ( c == '\n' ) {
			input[inputCount++] = '\0';
			break;
		}

		input[inputCount++] = c;
		if ( inputCount >= inputSize ) {
			inputSize *= 2;
			input = ( char * ) realloc( input, inputSize * sizeof( char ) );
		}
	}

	if ( !searchForInput( grid, input, inputCount ) ) {
		printf( "Slovo \"%s\" nenalezeno.\n", input );
		free( input );
		return 0;
	}

	if ( lastInput ) {
		printSelection( grid );
		free( input );
		return 0;
	} else {
		free( input );
		return 1;
	}
	return 1;
}

int main() {
	SGrid * grid = ( SGrid * ) malloc( sizeof( SGrid ) );
	grid->mHasStrip = 0;
	if ( loadMap( grid ) ) {
		printf( "Nespravny vstup.\n" );
		deleteGrid( grid );
		return 1;
	}

	while ( readQuery( grid ) ) {}

	deleteGrid( grid );

	return 0;
}