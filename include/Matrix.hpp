#pragma once
#include "Constants.hpp"
#include "Tetromino.hpp"
#include <array>
#include <optional>

class Matrix {
public:
  using Cell = std::optional<Tetromino::Type>;

  auto at(size_t x, size_t y) const -> Cell;
  auto at(Point<int> pos) const -> Cell;

  auto clear_lines() -> int;

  auto is_move_valid(const Tetromino::Shape &shape) const -> bool;

  void clear();

  void lock_down(Tetromino piece);

private:
  std::array<std::array<Cell, MATRIX_COLS>, MATRIX_ROWS> data_{};
};
