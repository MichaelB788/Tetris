#include "Matrix.hpp"
#include "Constants.hpp"
#include "Tetromino.hpp"
#include <algorithm>
#include <cassert>

auto Matrix::at(size_t x, size_t y) const -> Cell {
  assert(x < MATRIX_COLS && y < MATRIX_ROWS);
  return data_[y][x];
}

auto Matrix::at(Point<int> pos) const -> Cell {
  assert(0 <= pos.x && pos.x < MATRIX_COLS && 0 <= pos.x &&
         pos.y < MATRIX_ROWS);
  return data_[pos.y][pos.x];
}

void Matrix::clear() {
  for (auto &row : data_)
    row.fill(std::nullopt);
}

auto Matrix::is_shape_hitting_ground(const Tetromino::Shape &shape) const
    -> bool {
  for (const auto [x, y] : shape) {
    if (x < 0 || y < 0 || x >= MATRIX_COLS || y >= MATRIX_ROWS) {
      continue;
    }
    if (data_[y][x].has_value()) {
      return true;
    }
  }
  return false;
}

auto Matrix::is_move_valid(const Tetromino::Shape &shape) const -> bool {
  return std::ranges::all_of(shape, [this](auto pos) {
    return pos.x >= 0 && pos.y >= 0 && pos.x < MATRIX_COLS &&
           pos.y < MATRIX_ROWS && !data_[pos.y][pos.x].has_value();
  });
}

void Matrix::lock_down(Tetromino piece) {
  if (const auto shape = piece.get_shape(); is_move_valid(shape)) {
    for (const auto [x, y] : shape) {
      data_[y][x] = piece.get_type();
    }
  }
}

auto Matrix::clear_lines() -> unsigned {
  unsigned cleared = 0;
  int write = MATRIX_ROWS - 1;

  for (int read = MATRIX_ROWS - 1; read >= 0; --read) {
    if (std::ranges::all_of(data_[read], [](auto matrix_cell) {
          return matrix_cell.has_value();
        })) {
      ++cleared;
    } else {
      if (write != read) {
        data_[write] = data_[read];
      }
      --write;
    }
  }

  for (int i = write; i >= 0; --i)
    data_[i].fill(std::nullopt);

  return cleared;
}
