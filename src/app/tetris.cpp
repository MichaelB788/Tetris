#include "app/tetris.hpp"

Tetris::Tetris() : uiRenderer(renderer) {
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

	while ( !quit ) {
		renderer.clear();

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					EventHandler::handleInput(event, gameState);
					break;
				case SDL_WINDOWEVENT_RESIZED:
					window.updateWindowSize();
					break;
				default: break;
			}
		}

		// Temporary solution, change later
		if (timer % 20 == 0) gameState.moveDown();

		MatrixRenderer::render(gameState.getReferenceToMatrix(), renderer, window);
		uiRenderer.renderText(renderer, window);
		renderer.present();

		timer++;
		SDL_Delay(30);
	}

	printf("Score: %d lines\n", gameState.getScore());
}

