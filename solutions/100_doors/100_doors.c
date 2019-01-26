#include <stdio.h>

typedef enum { false = 0, true = 1 } opened;

static void show_states( opened all_doors[] ) {
	int whole_opened = 0, whole_closed = 0;

	for ( int i = 0; i < 100; ++i )
		if ( all_doors[i] ) {
			++whole_opened;
			printf( "door #%2d is opened\n", i + 1 );
		} else
			++whole_closed;

	printf( "Closed doors: %d\n"
	        "Opened doors: %d\n",
	        whole_closed, whole_opened );
}

static void visite_doors( int step, opened all_doors[] ) {
	for ( int i = step - 1; i < 100; i += step ) all_doors[i] = !all_doors[i];

	if ( step < 99 ) visite_doors( step + 1, all_doors );
}

int main( ) {
	opened all_doors[100] = { false };

	visite_doors( 1, all_doors );

	show_states( all_doors );
	return 0;
}
