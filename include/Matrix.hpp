#pragma once
#include "Tetromino.hpp"
#include <array>
#include <cassert>
#include <cstddef>
#include <optional>

class Matrix {
public:
  static constexpr size_t ROWS = 22, COLS = 10;
  using Cell = std::optional<Tetromino::Type>;

  auto at(size_t x, size_t y) const -> Cell;
  auto at(Point<int> pos) const -> Cell;

  auto clear_lines() -> int;

  auto is_move_valid(const Tetromino::Shape &shape) const -> bool;

  void clear();

  void lock_down(Tetromino piece);

private:
  std::array<std::array<Cell, COLS>, ROWS> data_{};
};
