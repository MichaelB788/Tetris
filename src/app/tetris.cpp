#include "app/tetris.hpp"

Tetris::Tetris() {
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) printf("Could not initialize SDL: %s\n", SDL_GetError());
	if ( TTF_Init() < 0 ) printf("Could not initialize SDL_TTF: %s\n", TTF_GetError());
	else runGameLoop();
}

Tetris::~Tetris() {
	TTF_Quit();
	SDL_Quit();
}

void Tetris::runGameLoop() {
	window.initializeSDLWindow("Tetris");
	renderer.initializeSDLRenderer(window.getWindow());
	if (!window.isInitialized() || !renderer.isInitialized()) return;

	uiRenderer.createTextTexture(renderer.getRenderer());
	SDL_Event event;
	bool quit = false;
	int timer = 0; // For testing, may need a more sophisticated method than this

	while ( !quit ) {
		renderer.clear();

		while (SDL_PollEvent(&event)) {
			window.handleWindowEvent(event);
			eventHandler.handleEvent(event, quit, gameState);
		}

		// Temporary solution, change later
		if (timer % 20 == 0) gameState.moveDown();

		matrixRenderer.render(gameState.getReferenceToMatrix(), renderer, window.getWindowSize());
		uiRenderer.renderText(renderer, window.getWindowSize());
		renderer.present();

		timer++;
		SDL_Delay(30);
	}

	printf("Score: %d lines\n", gameState.getScore());
}

