#include "BoardRenderer.hpp"
#include "Common.hpp"
#include "Matrix.hpp"
#include "pixel.hpp"
#include <SDL3/SDL_render.h>
#include <vector>

void BoardRenderer::draw_current(Tetromino::Projection current) {
  for (const auto &block : current.blocks)
    pixel::draw_tetromino_tile(renderer_, norm_atlas_,
                               pixel::texture_src(current.type), block,
                               offset_);
}

void BoardRenderer::draw_ghost(Tetromino::Projection ghost) {
  for (const auto &block : ghost.blocks)
    pixel::draw_tetromino_tile(renderer_, ghost_atlas_,
                               pixel::texture_src(ghost.type), block, offset_);
}

void BoardRenderer::draw_matrix(const Matrix &matrix) {
  std::array<std::vector<Point>, 8> grounded_rects;

  for (int y = 0; y < Matrix::ROWS; ++y) {
    for (int x = 0; x < Matrix::COLS; ++x) {
      MatrixCell cell = matrix.at(x, y);
      if (cell != MatrixCell::Empty)
        pixel::draw_tetromino_tile(renderer_, norm_atlas_,
                                   pixel::texture_src(cell), {x, y}, offset_);
    }
  }

  draw_matrix_outline();
}

void BoardRenderer::draw_matrix_outline() {
  const SDL_FRect outline = {.x = static_cast<float>(offset_.x * pixel::SIZE),
                             .y = static_cast<float>(offset_.y * pixel::SIZE),
                             .w = Matrix::COLS * pixel::SIZE,
                             .h = Matrix::ROWS * pixel::SIZE};
  static constexpr SDL_Color purple = {
      .r = 0x54, .g = 0x58, .b = 0xCC, .a = 0xFF};
  SDL_SetRenderDrawColor(renderer_, purple.r, purple.g, purple.b, purple.a);
  SDL_RenderRect(renderer_, &outline);
}
