#include "Matrix.hpp"
#include "FPoint.hpp"
#include "Piece.hpp"
#include <algorithm>
#include <cassert>

auto Matrix::clear_lines() -> unsigned {
  auto cleared = 0u;
  int write = ROWS - 1;

  for (int read = ROWS - 1; read >= 0; --read) {
    if (std::all_of(data[read].cbegin(), data[read].cend(),
                    [](auto tile) { return tile.has_value(); })) {
      ++cleared;
    } else {
      if (write != read)
        data[write] = data[read];
      --write;
    }
  }

  for (int i = write; i >= 0; --i)
    data[i].fill(std::nullopt);

  return cleared;
}

void Matrix::clear_all() {
  for (auto &row : data)
    row.fill(std::nullopt);
}

auto Matrix::is_fpos_within_bounds(FPoint pos) -> bool {
  return pos.x >= 0 && pos.y >= 0 && pos.x < COLS && pos.y < ROWS;
}

auto Matrix::is_fpos_valid_at(FPoint pos) const -> bool {
  return is_fpos_within_bounds(pos) && !data[pos.y][pos.x].has_value();
}

auto Matrix::at(FPoint pos) -> std::optional<Piece::Type> & {
  assert(is_fpos_within_bounds(pos));
  return data[static_cast<size_t>(pos.y)][static_cast<size_t>(pos.x)];
}

auto Matrix::at(FPoint pos) const -> std::optional<Piece::Type> {
  assert(is_fpos_within_bounds(pos));
  return data[static_cast<size_t>(pos.y)][static_cast<size_t>(pos.x)];
}
