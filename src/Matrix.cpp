#include "Matrix.hpp"
#include "Constants.hpp"
#include "Piece.hpp"
#include <algorithm>
#include <cassert>

namespace {
[[nodiscard]] auto is_pos_within_bounds(FPoint pos) -> bool {
  return pos.x >= 0 && pos.y >= 0 && pos.x < MATRIX_COLS && pos.y < MATRIX_ROWS;
}
} // namespace

auto Matrix::at(size_t x, size_t y) const -> std::optional<Piece::Type> {
  assert(x < MATRIX_COLS && y < MATRIX_ROWS);
  return data[y][x];
}

auto Matrix::at(FPoint pos) const -> std::optional<Piece::Type> {
  assert(is_pos_within_bounds(pos));
  return data[pos.y][pos.x];
}

void Matrix::clear() {
  for (auto &row : data)
    row.fill(std::nullopt);
}

auto Matrix::can_place(const Piece::Shape &shape) const -> bool {
  return std::ranges::all_of(shape, [this](auto pos) {
    return is_pos_within_bounds(pos) && !data[pos.y][pos.x].has_value();
  });
}

void Matrix::lock_down(Piece piece) {
  if (const auto shape = piece::create_shape(piece); can_place(shape)) {
    for (const auto [x, y] : shape)
      data[y][x] = piece.type;
  }
}

auto Matrix::clear_lines() -> unsigned {
  unsigned cleared = 0;
  int write = MATRIX_ROWS - 1;

  for (int read = MATRIX_ROWS - 1; read >= 0; --read) {
    if (std::ranges::all_of(data[read],
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

auto matrix::is_piece_within_bounds(const Piece::Shape &shape) -> bool {
  return std::ranges::all_of(
      shape, [](auto pos) { return is_pos_within_bounds(pos); });
}
