#include "render/tetris-paint.hpp"
#include "core/Matrix.hpp"
#include "core/Tetromino.hpp"
#include "util/Point.hpp"
#include <SDL3/SDL_render.h>
#include <array>
#include <vector>

namespace {
inline constexpr float COL_0 = 0, COL_1 = tetris::paint::TILE_SIZE,
                       COL_2 = tetris::paint::TILE_SIZE * 2,
                       COL_3 = tetris::paint::TILE_SIZE * 3;
inline constexpr float ROW_0 = 0, ROW_1 = tetris::paint::TILE_SIZE;

// Rectangles containing the textures corresponding to the Tetromino type
inline constexpr std::array<SDL_FRect, 8> tetromino_textures{{
    // I
    {.x = COL_0,
     .y = ROW_0,
     .w = tetris::paint::TILE_SIZE,
     .h = tetris::paint::TILE_SIZE},

    // O
    {.x = COL_1,
     .y = ROW_0,
     .w = tetris::paint::TILE_SIZE,
     .h = tetris::paint::TILE_SIZE},

    // T
    {.x = COL_2,
     .y = ROW_0,
     .w = tetris::paint::TILE_SIZE,
     .h = tetris::paint::TILE_SIZE},

    // S
    {.x = COL_3,
     .y = ROW_0,
     .w = tetris::paint::TILE_SIZE,
     .h = tetris::paint::TILE_SIZE},

    // Z
    {.x = COL_0,
     .y = ROW_1,
     .w = tetris::paint::TILE_SIZE,
     .h = tetris::paint::TILE_SIZE},

    // J
    {.x = COL_1,
     .y = ROW_1,
     .w = tetris::paint::TILE_SIZE,
     .h = tetris::paint::TILE_SIZE},

    // L
    {.x = COL_2,
     .y = ROW_1,
     .w = tetris::paint::TILE_SIZE,
     .h = tetris::paint::TILE_SIZE},
}};

void draw_tetromino_tile(Tetromino::Type type, SDL_Renderer &renderer,
                         SDL_Texture &atlas, Point pos, Point offset) {
  const SDL_FRect tetromino_rect = {
      .x = static_cast<float>(pos.x * tetris::paint::TILE_SIZE + offset.x),
      .y = static_cast<float>(pos.y * tetris::paint::TILE_SIZE + offset.y),
      .w = tetris::paint::TILE_SIZE,
      .h = tetris::paint::TILE_SIZE};

  SDL_RenderTexture(&renderer, &atlas, &tetromino_textures[type],
                    &tetromino_rect);
}

void draw_matrix_outline(SDL_Renderer &renderer, Point offset) {
  const SDL_FRect outline = {.x = static_cast<float>(offset.x),
                             .y = static_cast<float>(offset.y),
                             .w = Matrix::COLS * tetris::paint::TILE_SIZE,
                             .h = Matrix::ROWS * tetris::paint::TILE_SIZE};
  static constexpr SDL_Color purple = {
      .r = 0x54, .g = 0x58, .b = 0xCC, .a = 0xFF};

  SDL_SetRenderDrawColor(&renderer, purple.r, purple.g, purple.b, purple.a);
  SDL_RenderRect(&renderer, &outline);
}
} // namespace

void tetris::paint::tetromino(const Tetromino &tetromino,
                              SDL_Renderer &renderer, SDL_Texture &atlas,
                              Point offset) {
  for (const auto pos : tetromino.shape()) {
    draw_tetromino_tile(tetromino.type(), renderer, atlas, pos, offset);
  }
}

void tetris::paint::matrix(const Matrix &matrix, SDL_Renderer &renderer,
                           SDL_Texture &atlas, Point offset) {
  std::array<std::vector<Point>, 8> grounded_rects;

  for (int y = 0; y < Matrix::ROWS; ++y) {
    for (int x = 0; x < Matrix::COLS; ++x) {
      Point curr_pos = {x, y};
      if (matrix.at(curr_pos).has_value())
        draw_tetromino_tile(matrix.at(curr_pos).value(), renderer, atlas,
                            curr_pos, offset);
    }
  }

  draw_matrix_outline(renderer, offset);
}
