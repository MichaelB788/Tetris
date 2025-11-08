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
	Window m_window {"Tetris"};
	Renderer m_renderer {m_window};
	GameState m_gameState {m_renderer}; 
	EventHandler m_eventHandler {m_gameState};
};

#endif
