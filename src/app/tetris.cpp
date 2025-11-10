#include "app/tetris.hpp"
#include <cstdio>

Tetris::Tetris()
	: m_window("Tetris"), 
		m_renderer(m_window),
		m_gameState(m_renderer),
		m_eventHandler(m_gameState)
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
	int timer = 0; // For testing, may need a more sophisticated method than this

	while ( !quit ) {
		m_renderer.clearFrame();

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			} else if (event.type == SDL_KEYDOWN) {
				m_eventHandler.handleInput(event);
			}
		}

		if (timer % 50 == 0) m_gameState.moveActorDown();
		m_gameState.update();

		m_renderer.updateFrame();

		timer++;
		SDL_Delay(30);
	}
	{};
}

