#ifndef TETRIS_MATRIX_H
#define TETRIS_MATRIX_H
#include "Common.hpp"
#include <array>
#include <cassert>

class Matrix {
public:
  static constexpr std::size_t COLS = 10;
  static constexpr std::size_t ROWS = 20;

  Matrix() { clear(); };

  void clear();

  void place(TetrominoType type, std::size_t x, std::size_t y) {
    assert(is_within_bounds(x, y) && "Cannot place type out of bounds");
    matrix_[y][x] = static_cast<MatrixCell>(type);
  }

  [[nodiscard]] static bool is_within_bounds(std::size_t x, std::size_t y) {
    return x < COLS && y < ROWS;
  }

  [[nodiscard]] unsigned clear_lines();

  [[nodiscard]] bool pos_is_valid(std::size_t x, std::size_t y) const {
    return is_within_bounds(x, y) ? matrix_[y][x] == MatrixCell::Empty : false;
  }

  [[nodiscard]] MatrixCell at(std::size_t x, std::size_t y) const {
    assert(is_within_bounds(x, y) && "Cell is out of bounds");
    return matrix_[y][x];
  }

  [[nodiscard]] std::size_t cell_index(std::size_t x, std::size_t y) const {
    assert(is_within_bounds(x, y) && "Index is out of bounds");
    return static_cast<std::size_t>(matrix_[y][x]);
  }

  [[nodiscard]] std::size_t size() const { return matrix_.size(); }

private:
  [[nodiscard]] bool is_row_empty(std::size_t row) const;

  [[nodiscard]] bool is_row_full(std::size_t row) const;

  void clear_row(std::size_t row);

  void move_row(std::size_t src, std::size_t dest);

  unsigned clear_full_rows();

  void drop_rows();

  std::array<std::array<MatrixCell, COLS>, ROWS> matrix_{};
};

#endif
