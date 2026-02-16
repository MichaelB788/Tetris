#include "mechanics.hpp"
#include "Matrix.hpp"
#include <algorithm>

void mechanics::place(Tetromino::Projection tet, Matrix &matrix) {
  for (const auto &pos : tet.blocks)
    matrix.place(tet.type, pos.x, pos.y);
}

bool mechanics::can_place(Tetromino::Projection tet, const Matrix &matrix) {
  return std::ranges::all_of(
      tet.blocks.begin(), tet.blocks.end(),
      [&](const auto pos) { return matrix.pos_is_valid(pos.x, pos.y); });
}

bool mechanics::is_within_bounds(Tetromino::Projection tet) {
  return std::ranges::all_of(
      tet.blocks.begin(), tet.blocks.end(),
      [&](const auto pos) { return Matrix::is_within_bounds(pos.x, pos.y); });
}

bool mechanics::try_shift(Tetromino &tet, const Matrix &matrix, Point delta) {
  tet.shift(delta);

  if (mechanics::can_place(tet.projection(), matrix))
    return true;

  delta *= -1;
  tet.shift(delta);
  return false;
}

bool mechanics::try_spawn(Tetromino &tet, const Tetromino &new_tet,
                          const Matrix &matrix) {
  tet = new_tet;

  while (!mechanics::can_place(tet.projection(), matrix)) {
    tet.shift(Point{0, -1});
    if (!mechanics::is_within_bounds(tet.projection()))
      return false; // Fail
  }

  return true; // Success
}

void mechanics::drop(Tetromino &tet, const Matrix &matrix) {
  while (mechanics::can_place(tet.projection(), matrix))
    tet.shift(Point(0, 1));
  tet.shift(Point(0, -1));
}

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
  using OffsetData = std::array<std::array<Point, 5>, 4>;

  (tet.*rotation_func)();
  const OffsetData &offsets =
      tet.type() == TetrominoType::I ? srs_i_offsets : srs_offsets;

  for (std::size_t t = 0; t < 5; ++t) {
    Point kick_translation =
        offsets[tet.prev_rotation()][t] - offsets[tet.curr_rotation()][t];
    tet.shift(kick_translation);
    if (mechanics::can_place(tet.projection(), matrix))
      return true; // Success
  }

  return false; // Fail
}
} // namespace

void mechanics::srs::clockwise_rotation(Tetromino &tet, const Matrix &matrix) {
  if (tet.type() != TetrominoType::O) {
    Tetromino before = tet;
    if (srs_rotation(tet, &Tetromino::rotate_clockwise, matrix))
      return;
    else
      tet = before;
  }
}

void mechanics::srs::counterclockwise_rotation(Tetromino &tet,
                                               const Matrix &matrix) {
  if (tet.type() != TetrominoType::O) {
    Tetromino before = tet;
    if (srs_rotation(tet, &Tetromino::rotate_counterclockwise, matrix))
      return;
    else
      tet = before;
  }
}
