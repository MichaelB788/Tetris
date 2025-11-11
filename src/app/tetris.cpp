#include "app/tetris.hpp"
#include <cstdio>

Tetris::Tetris() : tetrominoController(gameState) {
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
		renderer.initializeSDLRenderer(window.sdlWindow);
	} else {
		return;
	}

	TetrominoController controller = {gameState};
	SDL_Event event;
	bool quit = false;
	int timer = 0; // For testing, may need a more sophisticated method than this

	while ( !quit ) {
		renderer.clearFrame();

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			} else if (event.type == SDL_KEYDOWN) {
				eventHandler.handleInput(event, controller);
			}
		}

		// Temporary solution, change later
		if (timer % 50 == 0) controller.moveActorDown();

		gameState.update();

		matrixRenderer.renderMatrixUsingSDL(gameState.matrix, renderer);
		renderer.updateFrame();

		timer++;
		SDL_Delay(30);
	}
	{};
}

