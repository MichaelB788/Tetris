#include "Matrix.hpp"
#include <algorithm>

unsigned Matrix::clear_lines() {
  const unsigned lines_cleared = clear_full_rows();

  if (lines_cleared == 0)
    return 0;

  drop_rows();
  return lines_cleared;
}

bool Matrix::is_row_empty(const std::size_t row) const {
  return std::ranges::all_of(
      matrix_[row].begin(), matrix_[row].end(),
      [](const MatrixCell cell) { return cell == MatrixCell::Empty; });
}

bool Matrix::is_row_full(const std::size_t row) const {
  return std::ranges::none_of(
      matrix_[row].begin(), matrix_[row].end(),
      [](const MatrixCell tile) { return tile == MatrixCell::Empty; });
}

void Matrix::clear_row(const std::size_t row) {
  for (auto &col : matrix_[row])
    col = MatrixCell::Empty;
}

void Matrix::move_row(const std::size_t src, const std::size_t dest) {
  for (std::size_t cell = 0; cell < COLS; ++cell)
    matrix_[dest][cell] = matrix_[src][cell];
  clear_row(src);
}

unsigned Matrix::clear_full_rows() {
  unsigned rows_cleared = 0;

  for (std::size_t row = 0; row < ROWS; ++row) {
    if (is_row_full(row)) {
      clear_row(row);
      rows_cleared++;
    }
  }

  return rows_cleared;
}

void Matrix::drop_rows() {
  int write = ROWS - 1;

  for (int read = ROWS - 1; read >= 0; --read) {
    if (!is_row_empty(read)) {
      if (write != read) {
        move_row(read, write);
      }
      --write;
    }
  }
}
