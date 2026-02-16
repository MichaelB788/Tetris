#include "BoardRenderer.hpp"
#include "Common.hpp"
#include "Matrix.hpp"
#include "pixel.hpp"
#include <SDL3/SDL_render.h>
#include <vector>

void BoardRenderer::draw_current(Tetromino::Projection current) {
  for (const auto &block : current.blocks)
    pixel::draw_tetromino_tile(renderer_, norm_atlas_,
                               pixel::get_texture(current.type), block,
                               offset_);
}

void BoardRenderer::draw_ghost(Tetromino::Projection ghost) {
  for (const auto &block : ghost.blocks)
    pixel::draw_tetromino_tile(renderer_, ghost_atlas_,
                               pixel::get_texture(ghost.type), block, offset_);
}

void BoardRenderer::draw_matrix(const Matrix &matrix) {
  std::array<std::vector<Point>, 8> grounded_rects;

  for (int y = 0; y < Matrix::ROWS; ++y) {
    for (int x = 0; x < Matrix::COLS; ++x) {
      MatrixCell cell = matrix.at(x, y);
      if (cell != MatrixCell::Empty)
        pixel::draw_tetromino_tile(renderer_, norm_atlas_,
                                   pixel::get_texture(cell), {x, y}, offset_);
    }
  }

  draw_matrix_outline();
}

void BoardRenderer::draw_matrix_outline() {
  std::array<SDL_FRect, Matrix::ROWS * Matrix::COLS> matrix_cells{};
  static constexpr SDL_Color black{.r = 0x00, .g = 0x00, .b = 0x00, .a = 0xFF};

  for (std::size_t y = 0; y < Matrix::ROWS; ++y) {
    for (std::size_t x = 0; x < Matrix::COLS; ++x) {
      matrix_cells[x + y * Matrix::COLS] = {
          static_cast<float>(x * pixel::SIZE + offset_.x),
          static_cast<float>(y * pixel::SIZE + offset_.y), pixel::SIZE,
          pixel::SIZE};
    }
  }

  SDL_SetRenderDrawColor(renderer_, black.r, black.g, black.b, black.a);
  SDL_RenderRects(renderer_, matrix_cells.data(), matrix_cells.size());
}
