#include "core/Matrix.hpp"
#include "core/Tetromino.hpp"
#include <algorithm>
#include <cassert>

auto Matrix::at(size_t x, size_t y) const -> Cell {
  assert(x < COLS && y < ROWS);
  return data_[y][x];
}

auto Matrix::at(Point<int> pos) const -> Cell {
  assert(0 <= pos.x && pos.x < COLS && 0 <= pos.x && pos.y < ROWS);
  return data_[pos.y][pos.x];
}

void Matrix::clear() {
  for (auto &row : data_)
    row.fill(std::nullopt);
}

auto Matrix::is_move_valid(const Tetromino::Shape &shape) const -> bool {
  return std::ranges::all_of(shape, [this](auto pos) {
    return 0 <= pos.x && pos.x < COLS && 0 <= pos.y && pos.y < ROWS &&
           !data_[pos.y][pos.x].has_value();
  });
}

void Matrix::lock_down(Tetromino piece) {
  auto shape = tetromino::shape_of(piece);
  if (is_move_valid(shape)) {
    for (const auto &pos : shape) {
      data_[pos.y][pos.x] = piece.type;
    }
  }
}

auto Matrix::clear_lines() -> int {
  int cleared = 0;
  int write = ROWS - 1;

  for (int read = ROWS - 1; read >= 0; --read) {
    if (std::ranges::all_of(data_[read], [](auto matrix_cell) {
          return matrix_cell.has_value();
        })) {
      ++cleared;
    } else {
      if (write != read)
        data_[write] = data_[read];
      --write;
    }
  }

  for (int i = write; i >= 0; --i)
    data_[i].fill(std::nullopt);

  return cleared;
}
