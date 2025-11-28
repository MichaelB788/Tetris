#include "app/tetris.hpp"
#include <random>

Tetris::Tetris(std::mt19937& gen)
	: window("Tetris"), renderer(window.getWindow()), ui(renderer), gameState(gen), eventHandler("../controls.ini") {
	if (!window.isInitialized() || !renderer.isInitialized()) return;
	else runGameLoop();
}

void Tetris::runGameLoop() {
	while ( !quit ) {
		renderer.clear();

		while (SDL_PollEvent(&event)) {
			window.handleWindowEvent(event);
			eventHandler.handle(event, gameState, quit);
		}

		if (ticks % difficulty == 0) gameState.moveDown();

		ui.render(gameState.getMatrix(), gameState.getQueue(), window.getWindowSize());
		renderer.present();

		ticks++;
		SDL_Delay(30);
	}

	printf("Score: %d lines\n", gameState.getScore());
}

