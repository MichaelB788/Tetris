#pragma once
#include "util/Point.hpp"
#include <SDL3/SDL_rect.h>

class SDL_Renderer;
class SDL_Texture;
class Tetromino;
class Matrix;

static constexpr float TILE_SIZE = 32;
namespace tetris::paint {
void tetromino(const Tetromino &tetromino, Point<float> offset,
               SDL_Renderer &renderer, SDL_Texture &atlas);

void matrix(const Matrix &matrix, Point<float> offset, SDL_Renderer &renderer,
            SDL_Texture &atlas);
} // namespace tetris::paint
