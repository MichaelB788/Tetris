#include "core/Tetris_Move.hpp"
#include "core/Matrix.hpp"
#include "core/Tetromino.hpp"
#include "util/Point.hpp"
#include <cstddef>

auto tetris::move::shift(Tetromino &piece, const Matrix &matrix, Point delta)
    -> bool {
  bool success = matrix.is_move_valid(piece.shifted(delta));
  if (success) {
    piece.pos += delta;
  }
  return success;
}

auto tetris::move::hard_drop_delta(const Tetromino &piece, const Matrix &matrix)
    -> Point {
  Point delta{.x = 0, .y = 0};
  while (matrix.is_move_valid(piece.shifted(delta + Point::down()))) {
    delta += Point::down();
  }
  return delta;
}

auto tetris::move::hard_dropped(const Tetromino &piece, const Matrix &matrix)
    -> Tetromino {
  auto dropped = piece;
  dropped.pos += hard_drop_delta(dropped, matrix);
  return dropped;
}

namespace {
constexpr size_t NUM_TRIALS = 5;
constexpr size_t MAX_ROTATIONS = 4;

constexpr Point STANDARD_PIECE_OFFSETS[MAX_ROTATIONS][NUM_TRIALS]{
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},       // R0
    {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},     // R90
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},       // R180
    {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}}; // R270

constexpr Point I_PIECE_OFFSETS[MAX_ROTATIONS][NUM_TRIALS]{
    {{0, 0}, {-1, 0}, {2, 0}, {-1, 0}, {2, 0}},     // R0
    {{-1, 0}, {0, 0}, {0, 0}, {0, -1}, {0, 2}},     // R90
    {{-1, -1}, {1, -1}, {-2, -1}, {1, 0}, {-2, 0}}, // R180
    {{0, -1}, {0, -1}, {0, -1}, {0, 1}, {0, -2}}};  // R270
} // namespace

void tetris::srs::rotation(Tetromino &piece, const Matrix &matrix,
                           RotationDir dir) {
  const auto prev = piece.rotation;
  const auto curr = dir == RotationDir::CW ? piece.rotation.incremented()
                                           : piece.rotation.decremented();

  const auto &offsets =
      piece.type == Tetromino::I ? I_PIECE_OFFSETS : STANDARD_PIECE_OFFSETS;
  for (size_t i = 0; i < NUM_TRIALS; ++i) {
    const Point kick = offsets[prev][i] - offsets[curr][i];
    if (matrix.is_move_valid(piece.shape_at(piece.pos + kick, curr))) {
      piece.rotation = curr;
      piece.pos += kick;
      return;
    }
  }
}
