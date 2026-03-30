#include "core/srs.hpp"
#include "core/Matrix.hpp"
#include "core/Tetromino.hpp"
#include "util/Point.hpp"
#include <cstddef>

namespace {
constexpr size_t NUM_TRIALS = 5;

constexpr Point srs_offsets[Tetromino::NUM_ROTATION][NUM_TRIALS]{
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},       // R0
    {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},     // R90
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},       // R180
    {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}}; // R270

constexpr Point srs_i_offsets[Tetromino::NUM_ROTATION][NUM_TRIALS]{
    {{0, 0}, {-1, 0}, {2, 0}, {-1, 0}, {2, 0}},     // R0
    {{-1, 0}, {0, 0}, {0, 0}, {0, -1}, {1, 2}},     // R90
    {{-1, -1}, {1, -1}, {-2, -1}, {1, 0}, {-2, 0}}, // R180
    {{0, -1}, {0, -1}, {0, -1}, {0, 1}, {0, -2}}};  // R270

using RotationFunc = void (Tetromino::*)();

void srs_rotation(Tetromino &target, const Matrix &matrix,
                  RotationFunc rotate) {
  const auto &offsets =
      target.type() == Tetromino::I ? srs_i_offsets : srs_offsets;
  Tetromino::Rotation prev = target.rotation();
  Tetromino::Rotation curr;

  (target.*rotate)();
  curr = target.rotation();

  for (size_t trial = 0; trial < NUM_TRIALS; ++trial) {
    Point kick = offsets[prev][trial] - offsets[curr][trial];
    if (matrix.is_move_valid(target.test_shift(kick))) {
      target.shift(kick);
      return; // Success
    }
  }

  target.set_rotation(prev); // Fail
}
} // namespace

void srs::rotate_cw(Tetromino &tet, const Matrix &matrix) {
  if (tet.type() != Tetromino::O) {
    srs_rotation(tet, matrix, &Tetromino::rotate_cw);
  }
}

void srs::rotate_ccw(Tetromino &tet, const Matrix &matrix) {
  if (tet.type() != Tetromino::O) {
    srs_rotation(tet, matrix, &Tetromino::rotate_ccw);
  }
}
