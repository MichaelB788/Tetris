#include "Matrix.hpp"
#include <algorithm>

namespace {} // namespace

int Matrix::clear_lines() {
  int cleared = clear_filled();
  if (cleared > 0) {
    drop_rows();
  }
  return cleared;
}

int Matrix::clear_filled() {
  unsigned cleared = 0;
  for (auto &row : data_) {
    if (std::ranges::all_of(row, is_filled)) {
      row.fill(Cell::EMPTY);
      ++cleared;
    }
  }
  return cleared;
}

void Matrix::drop_rows() {
  int write = ROWS - 1;
  for (int read = ROWS - 1; read >= 0; --read) {
    if (std::ranges::any_of(data_[read], is_filled)) {
      if (write != read) {
        data_[write] = data_[read];
        data_[read].fill(Cell::EMPTY);
      }
      --write;
    }
  }
}
