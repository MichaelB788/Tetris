#ifndef RENDER_H
#define RENDER_H
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_ttf.h>
#include <stdint.h>
#include "core/matrix.hpp"
#include "util/game-constants.hpp"

namespace Render {
	// TODO: Create textures for the basic Tetromino
	void rectangle(SDL_Renderer* renderer, unsigned int x, unsigned int y, unsigned int h, unsigned int w);
	void tetrisMatrix(SDL_Renderer* renderer, Matrix& matrix);
	void tetromino(SDL_Renderer* renderer, Matrix& matrix);
}

#endif
