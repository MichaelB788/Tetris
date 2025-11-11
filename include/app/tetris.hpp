#ifndef TETRIS_H
#define TETRIS_H
#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_render.h>

#include "util/window.hpp"
#include "util/renderer.hpp"

#include "render/matrix-renderer.hpp"

#include "core/game-state.hpp"
#include "core/tetromino-controller.hpp"
#include "core/event-handler.hpp"

class Tetris {
public:
  Tetris();
	~Tetris();

private:
	void runGameLoop();

private:
	GameState gameState; 

	Window window;
	Renderer renderer;
	MatrixRenderer matrixRenderer;

	EventHandler eventHandler;
	TetrominoController tetrominoController;
};

#endif
