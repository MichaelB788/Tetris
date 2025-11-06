#ifndef TETRIS_H
#define TETRIS_H
#include <SDL2/SDL.h>
#include "util/window.hpp"
#include "util/renderer.hpp"

class Tetris {
public:
  Tetris();

private:
	void runGameLoop();
	void updateFrame(SDL_Renderer* renderer);
};

#endif
