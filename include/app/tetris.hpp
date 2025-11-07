#ifndef TETRIS_H
#define TETRIS_H
#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include "util/window.hpp"
#include "util/renderer.hpp"
#include "core/game-state.hpp"
#include "render/matrix-renderer.hpp"

class Tetris {
public:
  Tetris();
	~Tetris();

private:
	void runGameLoop();
	Window m_window = Window("Tetris");
	Renderer m_renderer = Renderer(m_window);
	GameState m_state{m_renderer}; 
};

#endif
