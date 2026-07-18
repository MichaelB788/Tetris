#pragma once
#include "Constants.hpp"
#include "Tetromino.hpp"
#include <array>
#include <optional>

class Matrix {
public:
  using Cell = std::optional<Tetromino::Type>;

  [[nodiscard]] auto at(size_t x, size_t y) const -> Cell;
  [[nodiscard]] auto at(Point<int> pos) const -> Cell;

  void lock_down(Tetromino piece);
  auto clear_lines() -> unsigned;
  void clear();

  [[nodiscard]] auto
  is_shape_hitting_ground(const Tetromino::Shape &shape) const -> bool;
  [[nodiscard]] auto is_move_valid(const Tetromino::Shape &shape) const -> bool;

private:
  std::array<std::array<Cell, MATRIX_COLS>, MATRIX_ROWS> data{};
};
