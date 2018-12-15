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
			grid->mCountY++;
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

		if ( c != '\n' && c != '.' && ( c > 122 || c < 97 ) ) {
			free( grid->mGrid[grid->mCountY] );
			return -1;
		}

		if ( c == '\n' ) {
			if ( !first ) { break; }
			free( grid->mGrid[grid->mCountY] );
			return 1;
		}

		grid->mGrid[grid->mCountY][counter] = c;
		counter++;
		first = 0;
		if ( counter > grid->mCountX ) {
			free( grid->mGrid[grid->mCountY] );
			return -1;
		}



		if ( counter >= grid->mSizeX ) {
			grid->mSizeX *= 2;
			grid->mGrid[grid->mCountY] = ( char * ) realloc( grid->mGrid[grid->mCountY], grid->mSizeX * sizeof( char ) );
		}
	}

	if ( counter != grid->mCountX ) {
		free( grid->mGrid[grid->mCountY] );
		return -1;
	}

	grid->mSizeX = grid->mCountX;
	grid->mGrid[grid->mCountY] = ( char * ) realloc( grid->mGrid[grid->mCountY], grid->mSizeX * sizeof( char ) );

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
		for ( int j = 0 ; j < grid->mCountX ; ++j ) {
			grid->mStripGrid[i][j] = 0;
		}
	}
	grid->mHasStrip = 1;

	return 0;
}

void printSelection(SGrid * pGrid) {
	printf( "Vysledek:\n" );
	int cnt = 0, output = 0;
	for ( int i = 0 ; i < pGrid->mCountY ; ++i ) {
		for ( int j = 0 ; j < pGrid->mCountX ; ++j ) {
			if ( pGrid->mStripGrid[i][j] == 0 && pGrid->mGrid[i][j] != '.' ) {
				if ( cnt >= 60 ) {
					printf( "\n" );
					cnt = 0;
				}
				printf( "%c", pGrid->mGrid[i][j] );
				output = 1;
				cnt++;
			}
		}
	}
	if ( output ) {
		printf( "\n" );
	}
}

int tryNorth(SGrid * pGrid, const char * input, int inputSize, int startI, int startJ) {
	int i = startI, j = startJ;
	int k = 0, found = 0;
	while ( input[k] == pGrid->mGrid[i][j] ) {
		k++;
		if ( k >= inputSize - 1 ) {
			found = 1;
			break;
		}
		i--;
		if ( j < 0 || i >= pGrid->mCountY || j >= pGrid->mCountX || i < 0 ) {
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

int tryNorthWest(SGrid * pGrid, const char * input, int inputSize, int startI, int startJ) {
	int i = startI, j = startJ;
	int k = 0, found = 0;
	while ( input[k] == pGrid->mGrid[i][j] ) {
		k++;
		if ( k >= inputSize - 1 ) {
			found = 1;
			break;
		}
		i--;
		j--;
		if ( j < 0 || i >= pGrid->mCountY || j >= pGrid->mCountX || i < 0 ) {
			break;
		}
	}

	if ( found ) {
		for ( int l = k ; l > 0 ; --l ) {
			pGrid->mStripGrid[i][j] = 1;
			i++;
			j++;
		}
		return 1;
	}

	return 0;
}

int tryWest(SGrid * pGrid, const char * input, int inputSize, int startI, int startJ) {
	int i = startI, j = startJ;
	int k = 0, found = 0;
	while ( input[k] == pGrid->mGrid[i][j] ) {
		k++;
		if ( k >= inputSize - 1 ) {
			found = 1;
			break;
		}
		j--;
		if ( j < 0 || i >= pGrid->mCountY || j >= pGrid->mCountX || i < 0 ) {
			break;
		}
	}

	if ( found ) {
		for ( int l = k ; l > 0 ; --l ) {
			pGrid->mStripGrid[i][j] = 1;
			j++;
		}
		return 1;
	}

	return 0;
}

int trySouthWest(SGrid * pGrid, const char * input, int inputSize, int startI, int startJ) {
	int i = startI, j = startJ;
	int k = 0, found = 0;
	while ( input[k] == pGrid->mGrid[i][j] ) {
		k++;
		if ( k >= inputSize - 1 ) {
			found = 1;
			break;
		}
		i++;
		j--;
		if ( j < 0 || i >= pGrid->mCountY || j >= pGrid->mCountX || i < 0 ) {
			break;
		}
	}

	if ( found ) {
		for ( int l = k ; l > 0 ; --l ) {
			pGrid->mStripGrid[i][j] = 1;
			i--;
			j++;
		}
		return 1;
	}

	return 0;
}

int trySouth(SGrid * pGrid, const char * input, int inputSize, int startI, int startJ) {
	int i = startI, j = startJ;
	int k = 0, found = 0;
	while ( input[k] == pGrid->mGrid[i][j] ) {
		k++;
		if ( k >= inputSize - 1 ) {
			found = 1;
			break;
		}
		i++;
		if ( j < 0 || i >= pGrid->mCountY || j >= pGrid->mCountX || i < 0 ) {
			break;
		}
	}

	if ( found ) {
		for ( int l = k ; l > 0 ; --l ) {
			pGrid->mStripGrid[i][j] = 1;
			i--;
		}
		return 1;
	}

	return 0;
}

int trySouthEast(SGrid * pGrid, const char * input, int inputSize, int startI, int startJ) {
	int i = startI, j = startJ;
	int k = 0, found = 0;
	while ( input[k] == pGrid->mGrid[i][j] ) {
		k++;
		if ( k >= inputSize - 1 ) {
			found = 1;
			break;
		}
		i++;
		j++;
		if ( j < 0 || i >= pGrid->mCountY || j >= pGrid->mCountX || i < 0 ) {
			break;
		}
	}

	if ( found ) {
		for ( int l = k ; l > 0 ; --l ) {
			pGrid->mStripGrid[i][j] = 1;
			i--;
			j--;
		}
		return 1;
	}

	return 0;
}

int tryEast(SGrid * pGrid, const char * input, int inputSize, int startI, int startJ) {
	int i = startI, j = startJ;
	int k = 0, found = 0;
	while ( input[k] == pGrid->mGrid[i][j] ) {
		k++;
		if ( k >= inputSize - 1 ) {
			found = 1;
			break;
		}
		j++;
		if ( j < 0 || i >= pGrid->mCountY || j >= pGrid->mCountX || i < 0 ) {
			break;
		}
	}

	if ( found ) {
		for ( int l = k ; l > 0 ; --l ) {
			pGrid->mStripGrid[i][j] = 1;
			j--;
		}
		return 1;
	}

	return 0;
}

int tryNorthEast(SGrid * pGrid, const char * input, int inputSize, int startI, int startJ) {
	int i = startI, j = startJ;
	int k = 0, found = 0;
	while ( input[k] == pGrid->mGrid[i][j] ) {
		k++;
		if ( k >= inputSize - 1 ) {
			found = 1;
			break;
		}
		i--;
		j++;
		if ( j < 0 || i >= pGrid->mCountY || j >= pGrid->mCountX || i < 0 ) {
			break;
		}
	}

	if ( found ) {
		for ( int l = k ; l > 0 ; --l ) {
			pGrid->mStripGrid[i][j] = 1;
			i++;
			j--;
		}
		return 1;
	}

	return 0;
}

int searchForInput(SGrid * pGrid, char * input, int inputSize) {
	int found = 0;

	for ( int i = 0 ; i < pGrid->mCountY ; ++i ) {
		for ( int j = 0 ; j < pGrid->mCountX ; ++j ) {
			if ( tryNorth( pGrid, input, inputSize, i, j ) == 1 ) {
				found = 1;
			}
			if ( tryNorthWest( pGrid, input, inputSize, i, j ) == 1 ) {
				found = 1;
			}
			if ( tryWest( pGrid, input, inputSize, i, j ) == 1 ) {
				found = 1;
			}
			if ( trySouthWest( pGrid, input, inputSize, i, j ) == 1 ) {
				found = 1;
			}
			if ( trySouth( pGrid, input, inputSize, i, j ) == 1 ) {
				found = 1;
			}

			if ( trySouthEast( pGrid, input, inputSize, i, j ) == 1 ) {
				found = 1;
			}

			if ( tryEast( pGrid, input, inputSize, i, j ) == 1 ) {
				found = 1;
			}

			if ( tryNorthEast( pGrid, input, inputSize, i, j ) == 1 ) {
				found = 1;
			}
		}
	}

	if ( found == 0 ) {
		return 0;
	}

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

	if ( inputCount == 1 ) {
		printSelection( grid );
		free( input );
		return 0;
	}

	if ( !searchForInput( grid, input, inputCount ) ) {
		printf( "Slovo \'%s\' nenalezeno.\n", input );
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
