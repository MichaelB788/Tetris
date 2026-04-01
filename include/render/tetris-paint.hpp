#pragma once
#include "util/Point.hpp"
#include <SDL3/SDL_rect.h>

class SDL_Renderer;
class SDL_Texture;
class Tetromino;
class Matrix;

namespace tetris::paint {
constexpr float TILE_SIZE = 32;

void tetromino(const Tetromino &tetromino, SDL_Renderer &renderer,
               SDL_Texture &atlas, Point offset);

void matrix(const Matrix &matrix, SDL_Renderer &renderer, SDL_Texture &atlas,
            Point offset);
} // namespace tetris::paint
