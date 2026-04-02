#include "core/tetris-move.hpp"
#include "core/Matrix.hpp"
#include "core/Tetromino.hpp"
#include "util/Point.hpp"
#include <cstddef>

bool tetris::move::shift_piece(Tetromino &piece, const Matrix &matrix,
                               Point delta) {
  bool success = matrix.is_move_valid(piece.test_shift(delta));
  if (success) {
    piece.shift(delta);
  }
  return success;
}

Tetromino tetris::move::compute_dropped(const Tetromino &piece,
                                        const Matrix &matrix) {
  Tetromino dropped = piece;
  Point delta = {0, 0};
  while (matrix.is_move_valid(piece.test_shift(delta + Point::down()))) {
    delta += Point::down();
  }
  dropped.shift(delta);
  return dropped;
}

namespace {
constexpr size_t NUM_TRIALS = 5;

constexpr Point STANDARD_PIECE_OFFSETS[Tetromino::NUM_ROTATION][NUM_TRIALS]{
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},       // R0
    {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},     // R90
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},       // R180
    {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}}; // R270

constexpr Point I_PIECE_OFFSETS[Tetromino::NUM_ROTATION][NUM_TRIALS]{
    {{0, 0}, {-1, 0}, {2, 0}, {-1, 0}, {2, 0}},     // R0
    {{-1, 0}, {0, 0}, {0, 0}, {0, -1}, {0, 2}},     // R90
    {{-1, -1}, {1, -1}, {-2, -1}, {1, 0}, {-2, 0}}, // R180
    {{0, -1}, {0, -1}, {0, -1}, {0, 1}, {0, -2}}};  // R270

using RotationFunc = void (Tetromino::*)();

void srs_rotation(Tetromino &piece, const Matrix &matrix, RotationFunc rotate) {
  Tetromino::Rotation prev = piece.rotation();
  (piece.*rotate)();
  Tetromino::Rotation curr = piece.rotation();

  const auto &offsets =
      piece.type() == Tetromino::I ? I_PIECE_OFFSETS : STANDARD_PIECE_OFFSETS;
  for (size_t i = 0; i < NUM_TRIALS; ++i) {
    Point kick = offsets[prev][i] - offsets[curr][i];
    if (matrix.is_move_valid(piece.test_shift(kick))) {
      piece.shift(kick);
      return;
    }
  }

  piece.set_rotation(prev);
}
} // namespace

void tetris::srs::rotate_cw(Tetromino &tet, const Matrix &matrix) {
  if (tet.type() != Tetromino::O) {
    srs_rotation(tet, matrix, &Tetromino::rotate_cw);
  }
}

void tetris::srs::rotate_ccw(Tetromino &tet, const Matrix &matrix) {
  if (tet.type() != Tetromino::O) {
    srs_rotation(tet, matrix, &Tetromino::rotate_ccw);
  }
}
