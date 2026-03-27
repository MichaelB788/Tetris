#include "srs.hpp"
#include "Matrix.hpp"
#include "Tetromino.hpp"
#include <algorithm>

namespace {
constexpr std::array<std::array<Point, 5>, 4> srs_offsets{
    {{{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}},
     {{{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}}},
     {{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}},
     {{{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}}}};

constexpr std::array<std::array<Point, 5>, 4> srs_i_offsets{
    {{{{0, 0}, {-1, 0}, {2, 0}, {-1, 0}, {2, 0}}},
     {{{-1, 0}, {0, 0}, {0, 0}, {0, -1}, {1, 2}}},
     {{{-1, -1}, {1, -1}, {-2, -1}, {1, 0}, {-2, 0}}},
     {{{0, -1}, {0, -1}, {0, -1}, {0, 1}, {0, -2}}}}};

bool srs_rotation(Tetromino &tet, void (Tetromino::*rotation_func)(),
                  const Matrix &matrix) {
  const auto is_valid = [&](Point p) { return matrix.is_valid(p.x, p.y); };

  Tetromino::Rotation curr, prev = tet.rotation();

  (tet.*rotation_func)();
  curr = tet.rotation();

  auto &offsets = tet.type() == Tetromino::I ? srs_i_offsets : srs_offsets;
  for (std::size_t t = 0; t < 5; ++t) {
    Point kick = offsets[prev][t] - offsets[curr][t];
    tet.shift(kick);

    if (std::ranges::all_of(tet, is_valid))
      return true;
  }

  return false;
}
} // namespace

void srs::clockwise_rotation(Tetromino &tet, const Matrix &matrix) {
  if (tet.type() != Tetromino::O) {
    Tetromino before = tet;
    if (srs_rotation(tet, &Tetromino::rotate_clockwise, matrix))
      return;
    else
      tet = before;
  }
}

void srs::counterclockwise_rotation(Tetromino &tet, const Matrix &matrix) {
  if (tet.type() != Tetromino::O) {
    Tetromino before = tet;
    if (srs_rotation(tet, &Tetromino::rotate_counterclockwise, matrix))
      return;
    else
      tet = before;
  }
}
