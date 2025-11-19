#include "app/tetris.hpp"

Tetris::Tetris()
	: window("Tetris"),
		renderer(window.getWindow()),
		uiRenderer(renderer.getRenderer(), gameState)
{
	if (!window.isInitialized() || !renderer.isInitialized()) return;
	else runGameLoop();
}

void Tetris::runGameLoop() {
	SDL_Event event;
	bool quit = false;
	float timer = 0;
	int difficulty = 20;

	while ( !quit ) {
		renderer.clear();

		while (SDL_PollEvent(&event)) {
			window.handleWindowEvent(event);
			eventHandler.handleEvent(event, quit, gameState);
		}

		if (fmod(timer, difficulty) == 0) gameState.moveDown();

		matrixRenderer.render(gameState.getMatrix(), renderer, window.getWindowSize());
		uiRenderer.render(renderer, matrixRenderer);
		renderer.present();

		timer++;
		SDL_Delay(30);
	}

	printf("Score: %d lines\n", gameState.getScore());
}

