#ifndef TETRIS_H
#define TETRIS_H
#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_render.h>

#include "util/window.hpp"
#include "util/renderer.hpp"

#include "core/game-state.hpp"
#include "core/event-handler.hpp"

class Tetris {
public:
  Tetris();
	~Tetris();

private:
	void runGameLoop();

private:
	Window m_window;
	Renderer m_renderer;
	GameState m_gameState; 
	EventHandler m_eventHandler;
};

#endif
