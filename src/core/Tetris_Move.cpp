#include "core/Tetris_Move.hpp"
#include "core/Matrix.hpp"
#include "core/Tetromino.hpp"
#include "util/Point.hpp"
#include <cstddef>

auto tetris::move::shift(Tetromino &piece, const Matrix &matrix, Point delta)
    -> bool {
  if (matrix.is_move_valid(tetromino::shape_at(piece, piece.pos + delta))) {
    piece.pos += delta;
    return true;
  }
  return false;
}

void tetris::move::hard_drop(Tetromino &piece, const Matrix &matrix) {
  int delta_y = 0;
  while (matrix.is_move_valid(tetromino::shape_at(
      piece, piece.pos + Point{.x = 0, .y = delta_y + 1}))) {
    ++delta_y;
  }
  piece.pos.y += delta_y;
}

void tetris::srs::rotation(Tetromino &current, const Matrix &matrix,
                           RotationDir dir) {
  /**
   * Offset data for all Tetromino. The data can be parsed via the following
   * pattern:
   *
   * PIECE_OFFSETS[TetrominoRotation][Trial]
   */
  static constexpr Point STANDARD_PIECE_OFFSETS[4][5]{
      {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},       // R0
      {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},     // R90
      {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},       // R180
      {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}}; // R270
  static constexpr Point I_PIECE_OFFSETS[4][5]{
      {{0, 0}, {-1, 0}, {2, 0}, {-1, 0}, {2, 0}},     // R0
      {{-1, 0}, {0, 0}, {0, 0}, {0, -1}, {0, 2}},     // R90
      {{-1, -1}, {1, -1}, {-2, -1}, {1, 0}, {-2, 0}}, // R180
      {{0, -1}, {0, -1}, {0, -1}, {0, 1}, {0, -2}}};  // R270

  Tetromino rotated;
  switch (dir) {
    using enum RotationDir;
  case Clockwise:
    rotated = tetromino::rotated_clockwise(current);
    break;
  case CounterClockwise:
    rotated = tetromino::rotated_counterclockwise(current);
    break;
  case HalfTurn:
    rotated = tetromino::rotated_half_turn(current);
    break;
  }

  const auto &offsets =
      current.type == Tetromino::I ? I_PIECE_OFFSETS : STANDARD_PIECE_OFFSETS;
  const auto from = current.rotation, to = rotated.rotation;
  for (size_t i = 0; i < 5; ++i) {
    const Point kick = offsets[from][i] - offsets[to][i];
    if (matrix.is_move_valid(
            tetromino::shape_at(rotated, rotated.pos + kick))) {
      rotated.pos += kick;
      current = rotated;
      return;
    }
  }
}
