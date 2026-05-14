#include "render/Tetris_Paint.hpp"
#include "core/Matrix.hpp"
#include "core/Tetromino.hpp"
#include "util/Point.hpp"
#include <SDL3/SDL_render.h>
#include <array>
#include <vector>

namespace {
constexpr float COL_0 = 0, COL_1 = TILE_SIZE, COL_2 = TILE_SIZE * 2,
                COL_3 = TILE_SIZE * 3;
constexpr float ROW_0 = 0, ROW_1 = TILE_SIZE;

// Rectangles containing the textures corresponding to the Tetromino type
constexpr std::array<SDL_FRect, 8> tetromino_textures{{
    // I
    {.x = COL_0, .y = ROW_0, .w = TILE_SIZE, .h = TILE_SIZE},

    // O
    {.x = COL_1, .y = ROW_0, .w = TILE_SIZE, .h = TILE_SIZE},

    // T
    {.x = COL_2, .y = ROW_0, .w = TILE_SIZE, .h = TILE_SIZE},

    // S
    {.x = COL_3, .y = ROW_0, .w = TILE_SIZE, .h = TILE_SIZE},

    // Z
    {.x = COL_0, .y = ROW_1, .w = TILE_SIZE, .h = TILE_SIZE},

    // J
    {.x = COL_1, .y = ROW_1, .w = TILE_SIZE, .h = TILE_SIZE},

    // L
    {.x = COL_2, .y = ROW_1, .w = TILE_SIZE, .h = TILE_SIZE},
}};

void draw_tetromino_tile(Tetromino::Type type, Point<int> tetromino_pos,
                         Point<float> matrix_offset, SDL_Renderer &renderer,
                         SDL_Texture &atlas) {
  tetromino_pos *= TILE_SIZE;
  const SDL_FRect tetromino_rect = {.x = tetromino_pos.x + matrix_offset.x,
                                    .y = tetromino_pos.y + matrix_offset.y,
                                    .w = TILE_SIZE,
                                    .h = TILE_SIZE};

  SDL_RenderTexture(&renderer, &atlas, &tetromino_textures[type],
                    &tetromino_rect);
}
} // namespace

void tetris::paint::tetromino(const Tetromino &tetromino, Point<float> offset,
                              SDL_Renderer &renderer, SDL_Texture &atlas) {
  for (const auto pos : tetromino::shape_of(tetromino)) {
    draw_tetromino_tile(tetromino.type, pos, offset, renderer, atlas);
  }
}

void tetris::paint::matrix(const Matrix &matrix, Point<float> offset,
                           SDL_Renderer &renderer, SDL_Texture &atlas) {
  // Draw all locked pieces
  {
    std::array<std::vector<Point<int>>, 8> grounded_rects;

    for (int y = 0; y < Matrix::ROWS; ++y) {
      for (int x = 0; x < Matrix::COLS; ++x) {
        Point curr_pos = {x, y};
        if (matrix.at(curr_pos).has_value())
          draw_tetromino_tile(matrix.at(curr_pos).value(), curr_pos, offset,
                              renderer, atlas);
      }
    }
  }

  // Draw the matrix outline
  {
    const SDL_FRect outline_rect = {.x = offset.x,
                                    .y = offset.y,
                                    .w = Matrix::COLS * TILE_SIZE,
                                    .h = Matrix::ROWS * TILE_SIZE};
    SDL_SetRenderDrawColor(&renderer, 0x54, 0x58, 0xCC, 0xFF);
    SDL_RenderRect(&renderer, &outline_rect);
  }
}
