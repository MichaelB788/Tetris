#include "app/tetris.hpp"
#include <random>

Tetris::Tetris(std::mt19937& gen)
	: gameState(gen), window("Tetris"), renderer(window.getWindow()), ui(renderer) {
	if (!window.isInitialized() || !renderer.isInitialized()) return;
	else runGameLoop();
}

void Tetris::runGameLoop() {
	while ( !quit ) {
		renderer.clear();

		while (SDL_PollEvent(&event)) {
			window.handleWindowEvent(event);
			eventHandler.handleEvent(event, quit, gameState);
		}

		if (ticks % difficulty == 0) gameState.moveDown();

		ui.render(gameState, window.getWindowSize());
		renderer.present();

		ticks++;
		SDL_Delay(30);
	}

	printf("Score: %d lines\n", gameState.getScore());
}

