#include "app/tetris.hpp"
#include <cstdio>

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
				if (event.key.keysym.sym == SDLK_j)
					m_state.moveActorDown();
				if (event.key.keysym.sym == SDLK_h)
					m_state.moveActorLeft();
				if (event.key.keysym.sym == SDLK_l)
					m_state.moveActorRight();
				if (event.key.keysym.sym == SDLK_r)
					m_state.rotateActorClockwise();
				if (event.key.keysym.sym == SDLK_t)
					m_state.rotateActorClockwise();
			}
		}

		m_state.update();

		m_renderer.updateFrame();

		SDL_Delay(30);
	}
}

