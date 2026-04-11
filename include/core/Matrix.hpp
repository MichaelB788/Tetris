#pragma once
#include "core/Tetromino.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <optional>

class Matrix {
public:
  static constexpr size_t ROWS = 22, COLS = 10;

  using Cell = std::optional<Tetromino::Type>;

  void clear();

  void place(const Tetromino &piece);

  auto clear_lines() -> int;

  [[nodiscard]] static auto point_in_bounds(Point point) -> bool;

  [[nodiscard]] static auto shape_in_bounds(const Tetromino::Shape &shape)
      -> bool;

  [[nodiscard]] auto is_move_valid(const Tetromino::Shape &shape) const -> bool;

  [[nodiscard]] auto at(Point p) const -> Cell;

private:
  std::array<std::array<Cell, COLS>, ROWS> data_{};
};

inline void Matrix::clear() {
  for (auto &row : data_)
    row.fill(std::nullopt);
}

inline auto Matrix::point_in_bounds(Point point) -> bool {
  return 0 <= point.x && point.x < COLS && 0 <= point.y && point.y < ROWS;
}

inline auto Matrix::shape_in_bounds(const Tetromino::Shape &shape) -> bool {
  return std::ranges::all_of(shape, point_in_bounds);
}

inline auto Matrix::is_move_valid(const Tetromino::Shape &shape) const -> bool {
  return std::ranges::all_of(shape, [this](Point p) {
    return point_in_bounds(p) && !data_[p.y][p.x].has_value();
  });
}

inline auto Matrix::at(Point p) const -> Cell {
  assert(point_in_bounds(p));
  return data_[p.y][p.x];
}
