#include <stdio.h>
#include <stdlib.h>

// SDL2 include headers
#include <SDL.h>
#include <SDL_image.h>

const int WIDTH  = 430;
const int HEIGHT = 430;

SDL_Window *window = 0;

int initialization( ) {
	if ( SDL_Init( SDL_INIT_VIDEO ) ) {
		printf( "SDL_Init: %s\n", SDL_GetError( ) );
		return 0;
	}
	window = SDL_CreateWindow( "15 puzzle", SDL_WINDOWPOS_CENTERED,
	                           SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0 );
	if ( !window ) {
		printf( "SDL_CreateWindow: %s\n", SDL_GetError( ) );
		return 0;
	}
	int img_flags   = IMG_INIT_PNG;
	int img_initted = IMG_Init( img_flags );
	if ( ( img_initted & img_flags ) != img_flags ) {
		printf( "IMG_Init: %s\n", SDL_GetError( ) );
		return 0;
	}
	return 1;
}

SDL_Texture *make_texture( const char *path, SDL_Renderer *rend ) {
	SDL_Surface *surface = IMG_Load( path );
	if ( !surface ) {
		printf( "IMG_Load: %s\n", SDL_GetError( ) );
		return 0;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface( rend, surface );
	SDL_FreeSurface( surface );
	if ( !texture ) {
		printf( "SDL_CreateTextureFromSurface: %s\n", SDL_GetError( ) );
		return 0;
	}
	return texture;
}

void render_texture( SDL_Texture *texture, SDL_Renderer *rend, int x, int y ) {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture( texture, 0, 0, &dest.w, &dest.h );
	SDL_RenderCopy( rend, texture, 0, &dest );
}

int main( int argc, char *argv[] ) {
	if ( !initialization( ) ) {
		printf( "Initialization error\n" );
		SDL_Quit( );
	}

	SDL_Renderer *rend = SDL_CreateRenderer(
	    window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if ( !rend ) {
		SDL_DestroyWindow( window );
		printf( "SDL_CreateRenderer: %s\n", SDL_GetError( ) );
		SDL_Quit( );
		exit( EXIT_FAILURE );
	}

	SDL_Texture *puzzle_grid = make_texture( "./play_grid.png", rend );

	for ( int i = 0; i < 5; ++i ) {
		SDL_RenderClear( rend );

		render_texture( puzzle_grid, rend, 0, 0 );

		SDL_RenderPresent( rend );

		SDL_Delay( 1000 );
	}

	SDL_DestroyTexture( puzzle_grid );
	SDL_DestroyRenderer( rend );
	SDL_DestroyWindow( window );
	SDL_Quit( );

	// -Wunused-parameter
	(void)argc;
	(void)argv;

	return 0;
}
