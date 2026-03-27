#pragma once
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>

class Matrix {
public:
  static constexpr size_t ROWS = 20, COLS = 10;

  enum Cell : uint8_t { I = 0, O, T, S, Z, J, L, EMPTY = UINT8_MAX };

  Matrix() { clear(); }

public:
  void clear() {
    for (auto &row : data_)
      row.fill(EMPTY);
  }

  [[nodiscard]] int clear_lines();

public:
  [[nodiscard]] Cell &operator()(int x, int y) {
    assert(within_bounds(x, y));
    return data_[y][x];
  }

  [[nodiscard]] Cell operator()(int x, int y) const {
    assert(within_bounds(x, y));
    return data_[y][x];
  }

public:
  [[nodiscard]] static bool within_bounds(int x, int y) {
    return 0 <= x && x < COLS && 0 <= y && y < ROWS;
  }

  [[nodiscard]] static bool is_ground(Matrix::Cell cell) {
    return cell != EMPTY;
  }

  [[nodiscard]] bool is_valid(int x, int y) const {
    return within_bounds(x, y) && !is_ground(data_[y][x]);
  }

private:
  int clear_filled();

  void drop_rows();

private:
  std::array<std::array<Cell, COLS>, ROWS> data_{};
};
