#ifndef TETRIS_H
#define TETRIS_H
#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_ttf.h>

#include "render/ui-renderer.hpp"
#include "util/window.hpp"
#include "util/renderer.hpp"

#include "render/matrix-renderer.hpp"

#include "core/game-state.hpp"
#include "core/event-handler.hpp"

class Tetris {
public:
  Tetris();
	~Tetris();

private:
	void runGameLoop();

private:
	GameState gameState; 
	EventHandler eventHandler;

	Window window;
	Renderer renderer;
	UIRenderer uiRenderer;
	MatrixRenderer matrixRenderer;
};

#endif
