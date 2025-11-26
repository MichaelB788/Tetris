#include <SDL2/SDL.h>
#include "app/tetris.hpp"

int main (int argc, char **argv)
{
	bool sdlHasInit = SDL_Init(SDL_INIT_VIDEO) == 0;

	if ( !sdlHasInit ) printf("Could not initialize SDL: %s\n", SDL_GetError());

	// Run the game
	if ( sdlHasInit ) {
		static std::mt19937 gen{std::random_device{}()};
		Tetris app(gen);
	} 

	SDL_Quit();

	return 0;
}
