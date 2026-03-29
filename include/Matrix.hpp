#pragma once
#include "Point.hpp"
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>

class Matrix {
public:
  static constexpr size_t ROWS = 20, COLS = 10;

  enum Cell : uint8_t { I = 0, O, T, S, Z, J, L, EMPTY = UINT8_MAX };

  Matrix() { clear(); }

  void clear() {
    for (auto &row : data_)
      row.fill(EMPTY);
  }

  [[nodiscard]] int clear_lines();

  [[nodiscard]] Cell &at(Point point) {
    assert(within_bounds(point));
    return data_[point.y][point.x];
  }

  [[nodiscard]] Cell at(Point point) const {
    assert(within_bounds(point));
    return data_[point.y][point.x];
  }

  [[nodiscard]] static bool within_bounds(Point point) {
    return 0 <= point.x && point.x < COLS && 0 <= point.y && point.y < ROWS;
  }

  [[nodiscard]] static bool is_ground(Matrix::Cell cell) {
    return cell != EMPTY;
  }

  [[nodiscard]] bool is_valid(Point point) const {
    return within_bounds(point) && !is_ground(data_[point.y][point.x]);
  }

  struct IsPosValid {
    const Matrix &self;
    bool operator()(Point point) const { return self.is_valid(point); }
  };

private:
  int clear_filled();

  void drop_rows();

  std::array<std::array<Cell, COLS>, ROWS> data_{};
};
