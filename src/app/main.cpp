#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "app/tetris.hpp"

int main (int argc, char **argv)
{
	bool sdlHasInit = SDL_Init(SDL_INIT_VIDEO) == 0;
	bool ttfHasInit = TTF_Init() == 0;

	if ( !sdlHasInit ) printf("Could not initialize SDL: %s\n", SDL_GetError());
	if ( !ttfHasInit ) printf("Could not initialize SDL_TTF: %s\n", TTF_GetError());

	// Run the game
	if ( sdlHasInit && ttfHasInit ) Tetris app;

	TTF_Quit();
	SDL_Quit();

	return 0;
}
