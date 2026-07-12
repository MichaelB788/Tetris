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
  void clear();

  auto is_shape_hitting_ground(const Tetromino::Shape &shape) const -> bool;
  auto is_move_valid(const Tetromino::Shape &shape) const -> bool;
  void lock_down(Tetromino piece);

private:
  std::array<std::array<Cell, MATRIX_COLS>, MATRIX_ROWS> data_{};
};
