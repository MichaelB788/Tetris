#include "core/Matrix.hpp"
#include <algorithm>

void Matrix::place(const Tetromino &piece) {
  if (auto shape = piece.shape(); is_move_valid(shape)) {
    for (const auto &pos : shape) {
      data_[pos.y][pos.x] = piece.type;
    }
  }
}

auto Matrix::clear_lines() -> int {
  int cleared = 0;
  int write = ROWS - 1;

  const auto is_ground = [](Cell c) { return c.has_value(); };
  for (int read = ROWS - 1; read >= 0; --read) {
    if (std::ranges::all_of(data_[read], is_ground)) {
      ++cleared;
    } else {
      if (write != read)
        data_[write] = data_[read];
      --write;
    }
  }

  for (int i = write; i >= 0; --i)
    data_[i].fill(std::nullopt);

  return cleared;
}
