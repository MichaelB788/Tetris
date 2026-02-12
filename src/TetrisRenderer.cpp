#include "TetrisRenderer.hpp"
#include <array>
#include <vector>

namespace {
constexpr std::array<Color, 7> tetromino_colors{{
    {.r = 97, .g = 175, .b = 239, .a = 255},  // Cyan
    {.r = 229, .g = 222, .b = 123, .a = 255}, // Gold
    {.r = 198, .g = 120, .b = 221, .a = 255}, // Purple
    {.r = 152, .g = 195, .b = 121, .a = 255}, // Green
    {.r = 224, .g = 108, .b = 117, .a = 255}, // Coral red
    {.r = 86, .g = 88, .b = 194, .a = 255},   // Dark blue
    {.r = 209, .g = 154, .b = 102, .a = 255}, // Orange
}};
}

void TetrisRenderer::adjust_offset(int win_w, int win_h) {
  playfield_offset_.x = win_w - static_cast<int>(Matrix::COLS * tile_size_);
  playfield_offset_.y = win_h - static_cast<int>(Matrix::ROWS * tile_size_);
  playfield_offset_ /= 2;

  next_queue_offset_ = playfield_offset_ + Point(350, 0);
  hold_offset_ = playfield_offset_ - Point(300, 0);
}

void TetrisRenderer::draw_frame(const Tetris &tetris) {
  draw_tetromino(tetris.ghost(), playfield_offset_, Fill::Transparent,
                 Outline::Disabled);
  draw_tetromino(tetris.current(), playfield_offset_, Fill::Solid,
                 Outline::Disabled);
  draw_matrix(tetris.matrix());
  draw_next_queue(tetris.next_queue());
  if (tetris.hold().has_value())
    draw_tetromino(tetris.hold().value(), hold_offset_, Fill::Solid,
                   Outline::Enabled);
}

void TetrisRenderer::draw_matrix(const Matrix &matrix) {
  draw_grounded_tiles(matrix);
  draw_matrix_outline();
}

void TetrisRenderer::draw_next_queue(const NextQueue &queue) {
  Point queue_offset = next_queue_offset_;
  for (const auto &tetromino : queue) {
    draw_tetromino(tetromino, queue_offset, Fill::Solid, Outline::Enabled);
    queue_offset -= Point(0, -150);
  }
}

void TetrisRenderer::draw_tetromino(const Tetromino &tet, Point offset,
                                    Fill fill, Outline outline) {
  std::array<RectF, 4> tetromino_rects{};

  auto view = tet.view();
  for (std::size_t i = 0; i < view.size(); i++) {
    tetromino_rects[i] = {static_cast<float>(view[i].x * tile_size_ + offset.x),
                          static_cast<float>(view[i].y * tile_size_ + offset.y),
                          tile_size_, tile_size_};
  }

  const uint8_t alpha = fill == Fill::Transparent ? 100 : 255;
  Color color = tetromino_colors[tet.type_index()];
  color.a = alpha;

  if (fill != Fill::None) {
    renderer_.set_color(color);
    renderer_.render_fill_rects(tetromino_rects);
  }

  if (outline == Outline::Enabled) {
    renderer_.set_color({.r = 0, .g = 0, .b = 0, .a = alpha});
    renderer_.render_rects(tetromino_rects);
  }
}

void TetrisRenderer::draw_grounded_tiles(const Matrix &matrix) {
  std::array<std::vector<RectF>, 7> grounded_rects;

  for (std::size_t y = 0; y < Matrix::ROWS; ++y) {
    for (std::size_t x = 0; x < Matrix::COLS; ++x) {
      if (matrix.at(x, y) != MatrixCell::Empty) {
        grounded_rects[matrix.cell_index(x, y)].push_back(
            {.x = static_cast<float>(x * tile_size_ + playfield_offset_.x),
             .y = static_cast<float>(y * tile_size_ + playfield_offset_.y),
             .w = tile_size_,
             .h = tile_size_});
      }
    }
  }

  for (std::size_t tetromino_type = 0; tetromino_type < 7; ++tetromino_type) {
    if (!grounded_rects[tetromino_type].empty()) {
      renderer_.set_color(tetromino_colors[tetromino_type]);
      renderer_.render_fill_rects(grounded_rects[tetromino_type]);
    }
  }
}

void TetrisRenderer::draw_matrix_outline() {
  std::array<RectF, Matrix::ROWS * Matrix::COLS> matrix_cells{};

  for (std::size_t y = 0; y < Matrix::ROWS; ++y) {
    for (std::size_t x = 0; x < Matrix::COLS; ++x) {
      matrix_cells[x + y * Matrix::COLS] = {
          static_cast<float>(x * tile_size_ + playfield_offset_.x),
          static_cast<float>(y * tile_size_ + playfield_offset_.y), tile_size_,
          tile_size_};
    }
  }

  renderer_.set_color({.r = 0, .g = 0, .b = 0, .a = 255});
  renderer_.render_rects(matrix_cells);
}
