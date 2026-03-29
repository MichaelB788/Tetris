#include "Matrix.hpp"
#include <algorithm>

int Matrix::clear_lines() {
  const auto is_ground = [](Cell c) { return c.has_value(); };
  int cleared = 0;
  int write = ROWS - 1;

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
