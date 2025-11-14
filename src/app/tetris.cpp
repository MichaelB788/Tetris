#include "app/tetris.hpp"
#include <SDL_video.h>
#include <cstdio>

Tetris::Tetris() {
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
	if (window.initializeSDLWindow("Tetris")) {
		renderer.initializeSDLRenderer(window.getWindow());
	} else {
		return;
	}

	SDL_Event event;
	bool quit = false;
	int timer = 0; // For testing, may need a more sophisticated method than this
	int winWidth, winHeight;

	while ( !quit ) {
		renderer.clearFrame();

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			} else if (event.type == SDL_KEYDOWN) {
				eventHandler.handleInput(event, gameState);
			} else if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				window.updateWindowDimensions();
			}
		}

		// Temporary solution, change later
		if (timer % 50 == 0) gameState.moveDown();

		MatrixRenderer::renderMatrixUsingSDL(gameState.getReferenceToMatrix(), renderer, window);
		renderer.updateFrame();

		timer++;
		SDL_Delay(30);
	}

	printf("Score: %d lines\n", gameState.getScore());
}

