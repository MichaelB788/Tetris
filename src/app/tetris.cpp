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
}

Tetris::~Tetris() {
	SDL_Quit();
}

void Tetris::runGameLoop() {
	m_renderer.initializeSDLRenderer();
	SDL_Event event;
	bool quit = false;

	while ( !quit ) {
		m_renderer.clearFrame();

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			} else if (event.type == SDL_KEYDOWN) {
				// Handle event
			}
		}

		m_state.update();

		m_renderer.updateFrame();

		SDL_Delay(100);
	}
}

