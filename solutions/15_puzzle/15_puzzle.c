#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// SDL2 include headers
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define log_er( str )                               \
	{                                               \
		printf( "%s: %s\n", str, SDL_GetError( ) ); \
		return 0;                                   \
	}

#define termination_er( str )                       \
	{                                               \
		printf( "%s: %s\n", str, SDL_GetError( ) ); \
		SDL_Quit( );                                \
		exit( EXIT_FAILURE );                       \
	}

const int WIDTH  = 430;
const int HEIGHT = 430;

SDL_Window *window = 0;

static int initialization( ) {
	if ( SDL_Init( SDL_INIT_VIDEO ) ) log_er( "SDL_Init" );

	window = SDL_CreateWindow( "15 puzzle", SDL_WINDOWPOS_CENTERED,
	                           SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0 );
	if ( !window ) log_er( "SDL_CreateWindow" );

	int img_flags   = IMG_INIT_PNG;
	int img_initted = IMG_Init( img_flags );
	if ( ( img_initted & img_flags ) != img_flags ) log_er( "ING_Init" );

	return 1;
}

static SDL_Texture *make_texture( const char *path, SDL_Renderer *rend ) {
	SDL_Surface *surface = IMG_Load( path );
	if ( !surface ) log_er( "IMG_Load" );

	SDL_Texture *texture = SDL_CreateTextureFromSurface( rend, surface );
	SDL_FreeSurface( surface );
	if ( !texture ) log_er( "SDL_CreateTextureFromSurface" );

	return texture;
}

static void render_texture( SDL_Texture *texture, SDL_Renderer *rend, int x, int y ) {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture( texture, 0, 0, &dest.w, &dest.h );
	SDL_RenderCopy( rend, texture, 0, &dest );
}

int main( int argc, char *argv[] ) {
	if ( !initialization( ) ) termination_er( "Initialization error" );

	SDL_Renderer *rend = SDL_CreateRenderer(
	    window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if ( !rend ) {
		SDL_DestroyWindow( window );
		termination_er( "SDL_CreateRenderer" );
	}

	SDL_Texture *puzzle_grid = make_texture( "./play_grid.png", rend );

	SDL_Event e;
	bool      play_game = true;
	while ( play_game ) {
		while ( SDL_PollEvent( &e ) ) {
			if ( e.type == SDL_QUIT )
				play_game = false;
			else if ( e.type == SDL_KEYDOWN ) {
				switch ( e.key.keysym.sym ) {
					case SDLK_ESCAPE: play_game = false; break;
					case SDLK_UP: puts( "UP" ); break;
					case SDLK_DOWN: puts( "DOWN" ); break;
					case SDLK_LEFT: puts( "LEFT" ); break;
					case SDLK_RIGHT: puts( "RIGHT" ); break;
				}
			}
		}

		SDL_RenderClear( rend );

		render_texture( puzzle_grid, rend, 0, 0 );

		SDL_RenderPresent( rend );
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
