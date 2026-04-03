#pragma once
#include "core/Tetromino.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <optional>

class Matrix {
public:
  static constexpr size_t ROWS = 20, COLS = 10;

  using Cell = std::optional<Tetromino::Type>;

  void clear() {
    for (auto &row : data_)
      row.fill(std::nullopt);
  }

  void place(const Tetromino &piece);

  auto clear_lines() -> int;

  [[nodiscard]] static auto point_in_bounds(Point point) -> bool {
    return 0 <= point.x && point.x < COLS && 0 <= point.y && point.y < ROWS;
  }

  [[nodiscard]] static auto shape_in_bounds(const Tetromino::Shape &shape)
      -> bool {
    return std::ranges::all_of(shape, point_in_bounds);
  }

  [[nodiscard]] auto is_move_valid(const Tetromino::Shape &shape) const
      -> bool {
    return std::ranges::all_of(shape, [this](Point p) {
      return point_in_bounds(p) && !data_[p.y][p.x].has_value();
    });
  }

  [[nodiscard]] auto at(Point p) const -> Cell {
    assert(point_in_bounds(p));
    return data_[p.y][p.x];
  }

private:
  std::array<std::array<Cell, COLS>, ROWS> data_{};
};
