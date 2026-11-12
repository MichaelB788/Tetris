#include "Playfield.hpp"
#include "Geometry.hpp"
#include "Piece.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>

namespace {
constexpr Rectangle BOUNDS = {0, 0, Playfield::COLS - 1, Playfield::ROWS - 1};
}

void Playfield::clear_all_rows() {
  for (auto &row : cells)
    row.fill(std::nullopt);
}

auto Playfield::clear_full_rows() -> unsigned {
  auto cleared = 0u;
  int write = ROWS - 1;

  for (int read = ROWS - 1; read >= 0; --read) {
    if (std::all_of(cells[read].cbegin(), cells[read].cend(),
                    [](Cell cell) { return cell.has_value(); })) {
      ++cleared;
    } else {
      if (write != read)
        cells[write] = cells[read];
      --write;
    }
  }

  for (int i = write; i >= 0; --i)
    cells[i].fill(std::nullopt);

  return cleared;
}

void Playfield::lock_down(const Piece &piece) {
  const auto shape = piece.get_shape();
  const auto type = piece.get_type();
  assert(can_place(shape));
  for (const auto p : shape)
    cells[static_cast<size_t>(p.y)][static_cast<size_t>(p.x)] = type;
}

auto Playfield::is_within_bounds(const Piece::Shape &shape) -> bool {
  return std::all_of(shape.cbegin(), shape.cend(),
                     [](Point p) { return p.is_within(BOUNDS); });
}

auto Playfield::can_place(const Piece::Shape &shape) const -> bool {
  return std::all_of(shape.cbegin(), shape.cend(), [this](Point p) {
    return p.is_within(BOUNDS) &&
           !cells[static_cast<size_t>(p.y)][static_cast<size_t>(p.x)]
                .has_value();
  });
}

auto Playfield::at(Point pos) const -> Cell {
  assert(pos.is_within(BOUNDS));
  return cells[static_cast<size_t>(pos.y)][static_cast<size_t>(pos.x)];
}

auto Playfield::operator()(size_t x, size_t y) const -> Cell {
  assert(x < COLS && y < ROWS);
  return cells[y][x];
}
