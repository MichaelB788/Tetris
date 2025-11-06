#include "app/tetris.hpp"
#include <SDL_events.h>
#include <SDL_render.h>

Tetris::Tetris()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	} else {
		runGameLoop();
	}

	SDL_Quit();
}


void Tetris::runGameLoop() {
	SDL_Event event;
	Window window = Window("Tetris");
	Renderer renderer = Renderer(window);
	bool quit = false;

	while ( !quit ) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			} else if (event.type == SDL_KEYDOWN) {
				// Handle event
			}
		}

		m_state.update();

		updateFrame(renderer.getSDLRendererPointer());

		SDL_Delay(100);
	}
}

void Tetris::updateFrame(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}
