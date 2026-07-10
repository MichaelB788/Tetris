#pragma once
#include "PlatformSDL.hpp"
#include "Point.hpp"
#include "Tetromino.hpp"

namespace tetris::renderer {
void draw_tetromino(Tetromino tet, Point<float> screen_offset,
                    SDL_Renderer &renderer, SDL_Texture &texture_atlas);

void draw_ghost(Tetromino tet, Point<float> screen_offset,
                SDL_Renderer &renderer, SDL_Texture &texture_atlas);

void draw_matrix(const Matrix &matrix, Point<float> screen_offset,
                 SDL_Renderer &renderer, SDL_Texture &texture_atlas);
} // namespace tetris::renderer
