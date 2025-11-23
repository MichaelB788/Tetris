#ifndef TETRIS_H
#define TETRIS_H
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <cmath>
#include <random>

#include "render/ui.hpp"
#include "util/window.hpp"
#include "util/renderer.hpp"
#include "core/game-state.hpp"
#include "core/event-handler.hpp"

class Tetris {
public:
  Tetris();

private:
	void runGameLoop();

private:
	GameState gameState; 
	EventHandler eventHandler;

	Window window;
	Renderer renderer;
	UI ui;

	float timer = 0;
	int difficulty = 20;
	SDL_Event event;
	bool quit = false;

	std::random_device rd;
	std::mt19937 gen{rd()};
};

#endif
