#ifndef TETRIS_H
#define TETRIS_H
#include <SDL2/SDL.h>
#include "core/tetromino.hpp"
#include "core/matrix.hpp"
#include "util/window.hpp"
#include "util/renderer.hpp"

class Tetris {
public:
  Tetris();

private:
	GameContext m_gameContext;
	ScreenContext m_screenContext;
  void update();
	void gameLoop();
};

#endif
