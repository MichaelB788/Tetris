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

  [[nodiscard]] static bool out_of_bounds(int x, int y) {
    return 0 <= x && x < Matrix::COLS && 0 <= y && y < Matrix::ROWS;
  }

  [[nodiscard]] static bool is_filled(Matrix::Cell cell) {
    return cell != Matrix::Cell::EMPTY;
  }

public:
  [[nodiscard]] Cell &operator()(size_t x, size_t y) {
    assert(!out_of_bounds(x, y));
    return data_[y][x];
  }

  [[nodiscard]] Cell operator()(size_t x, size_t y) const {
    assert(!out_of_bounds(x, y));
    return data_[y][x];
  }

private:
  int clear_filled();

  void drop_rows();

private:
  std::array<std::array<Cell, COLS>, ROWS> data_{};
};
