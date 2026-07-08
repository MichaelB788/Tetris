#include "TetrisRenderer.hpp"
#include "Constants.hpp"
#include "Matrix.hpp"
#include "Point.hpp"
#include "Tetromino.hpp"
#include <SDL3/SDL_render.h>
#include <array>
#include <vector>

void draw_tile(Tetromino::Type type, Point<int> matrix_pos,
               Point<float> screen_offset, bool ghost_tile,
               SDL_Renderer &renderer, SDL_Texture &texture_atlas) {
  const SDL_FRect texture_rect = {.x = PIXEL_SCALE * static_cast<float>(type),
                                  .y = ghost_tile ? PIXEL_SCALE : 0,
                                  .w = PIXEL_SCALE,
                                  .h = PIXEL_SCALE};

  const SDL_FRect texture_screen_pos = {
      .x = static_cast<float>(matrix_pos.x) * PIXEL_SCALE + screen_offset.x,
      .y = static_cast<float>(matrix_pos.y) * PIXEL_SCALE + screen_offset.y,
      .w = PIXEL_SCALE,
      .h = PIXEL_SCALE};

  SDL_RenderTexture(&renderer, &texture_atlas, &texture_rect,
                    &texture_screen_pos);
}

void TetrisRenderer::draw_tetromino(Tetromino tet, Point<float> screen_offset,
                                    SDL_Renderer &renderer,
                                    SDL_Texture &texture_atlas) {
  for (const auto pos : shape_of(tet)) {
    draw_tile(tet.type, pos, screen_offset, false, renderer, texture_atlas);
  }
}

void TetrisRenderer::draw_ghost(Tetromino tet, Point<float> screen_offset,
                                SDL_Renderer &renderer,
                                SDL_Texture &texture_atlas) {
  for (const auto pos : shape_of(tet)) {
    draw_tile(tet.type, pos, screen_offset, true, renderer, texture_atlas);
  }
}

void draw_locked_tiles(const Matrix &matrix, Point<float> screen_offset,
                       SDL_Renderer &renderer, SDL_Texture &texture_atlas) {
  std::array<std::vector<Point<int>>, 7> grounded_rects;

  for (int y = 0; y < MATRIX_ROWS; ++y) {
    for (int x = 0; x < MATRIX_COLS; ++x) {
      if (auto tile = matrix.at(x, y)) {
        draw_tile(tile.value(), {x, y}, screen_offset, false, renderer,
                  texture_atlas);
      }
    }
  }
}

void draw_outline(Point<float> screen_offset, SDL_Renderer &renderer) {
  const SDL_FRect outline_rect = {.x = screen_offset.x,
                                  .y = screen_offset.y,
                                  .w = MATRIX_COLS * PIXEL_SCALE,
                                  .h = MATRIX_ROWS * PIXEL_SCALE};
  SDL_SetRenderDrawColor(&renderer, 0x54, 0x58, 0xCC, 0xFF);
  SDL_RenderRect(&renderer, &outline_rect);
}

void TetrisRenderer::draw_matrix(const Matrix &matrix,
                                 Point<float> screen_offset,
                                 SDL_Renderer &renderer,
                                 SDL_Texture &texture_atlas) {
  draw_locked_tiles(matrix, screen_offset, renderer, texture_atlas);
  draw_outline(screen_offset, renderer);
}
