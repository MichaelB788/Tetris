#include "Matrix.hpp"
#include "Constants.hpp"
#include "Tetromino.hpp"
#include <algorithm>
#include <cassert>

namespace {
[[nodiscard]] auto is_pos_within_bounds(FPoint pos) -> bool {
  return pos.x >= 0 && pos.y >= 0 && pos.x < MATRIX_COLS && pos.y < MATRIX_ROWS;
}
} // namespace

auto Matrix::at(size_t x, size_t y) const -> std::optional<Tetromino::Type> {
  assert(x < MATRIX_COLS && y < MATRIX_ROWS);
  return data[y][x];
}

auto Matrix::at(FPoint pos) const -> std::optional<Tetromino::Type> {
  assert(is_pos_within_bounds(pos));
  return data[pos.y][pos.x];
}

void Matrix::clear() {
  for (auto &row : data)
    row.fill(std::nullopt);
}

[[nodiscard]] auto Matrix::is_out_of_bounds(const Tetromino::Shape &shape)
    -> bool {
  for (const auto pos : shape) {
    if (!is_pos_within_bounds(pos))
      return true;
  }
  return false;
}

auto Matrix::is_move_valid(const Tetromino::Shape &shape) const -> bool {
  return std::ranges::all_of(shape, [this](auto pos) {
    return pos.x >= 0 && pos.y >= 0 && pos.x < MATRIX_COLS &&
           pos.y < MATRIX_ROWS && !data[pos.y][pos.x].has_value();
  });
}

void Matrix::lock_down(Tetromino piece) {
  if (const auto shape = piece.get_shape(); is_move_valid(shape)) {
    for (const auto [x, y] : shape) {
      data[y][x] = piece.get_type();
    }
  }
}

auto Matrix::clear_lines() -> unsigned {
  unsigned cleared = 0;
  int write = MATRIX_ROWS - 1;

  for (int read = MATRIX_ROWS - 1; read >= 0; --read) {
    if (std::ranges::all_of(data[read], [](auto matrix_cell) {
          return matrix_cell.has_value();
        })) {
      ++cleared;
    } else {
      if (write != read) {
        data[write] = data[read];
      }
      --write;
    }
  }

  for (int i = write; i >= 0; --i)
    data[i].fill(std::nullopt);

  return cleared;
}
