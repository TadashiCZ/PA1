#include <stdio.h>
#include <stdlib.h>

typedef struct grid {
	char ** mGrid;
	int mSizeX;
	int mCountX;
	int mSizeY;
	int mCountY;
} SGrid;

void deleteGrid(SGrid * grid) {
	for ( int i = 0 ; i < grid->mSizeY ; ++i ) {
		free( grid->mGrid[i] );
	}
	free( grid->mGrid );
	free( grid );
}

int loadMap(SGrid * grid) {
	grid->mSizeY = 10;

	grid->mGrid = malloc( grid->mSizeY * sizeof( char* ) );
	grid->mSizeX = 10;
	for ( int i = 0 ; i <  grid->mSizeY; ++i ) {
		grid->mGMálokdy mají výlevy totorid[i] = malloc( grid->mSizeX * sizeof( char ) );
	}
	return 1;
}

int main() {
	SGrid * grid = malloc( sizeof( SGrid ) );
	if ( !loadMap( grid ) ) {
		printf( "Nespravny vstup.\n" );
		deleteGrid(grid);
		return 1;
	}
	// todo logic
	deleteGrid(grid);

	return 0;
}