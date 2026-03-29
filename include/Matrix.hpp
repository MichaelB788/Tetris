#pragma once
#include "Tetromino.hpp"
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

  void place(const Tetromino &piece) {
    if (is_move_valid(piece))
      for (const auto &pos : piece.shape())
        data_[pos.y][pos.x] = piece.type();
  }

  int clear_lines();

  [[nodiscard]] static bool within_bounds(Point point) {
    return 0 <= point.x && point.x < COLS && 0 <= point.y && point.y < ROWS;
  }

  [[nodiscard]] bool is_move_valid(const Tetromino &piece) const {
    return std::ranges::all_of(piece.shape(), [this](Point p) {
      return within_bounds(p) && !data_[p.y][p.x].has_value();
    });
  }

  [[nodiscard]] Cell at(Point p) const {
    assert(within_bounds(p));
    return data_[p.y][p.x];
  }

private:
  std::array<std::array<Cell, COLS>, ROWS> data_{};
};
