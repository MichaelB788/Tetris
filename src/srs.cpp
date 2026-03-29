#include "srs.hpp"
#include "Matrix.hpp"
#include "Point.hpp"
#include "Tetromino.hpp"
#include <algorithm>
#include <cstdint>

namespace {
constexpr uint8_t NUM_TRIALS = 5;

constexpr Point srs_offsets[NUM_ROTATIONS][NUM_TRIALS]{
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},       // R0
    {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},     // R90
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},       // R180
    {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}}; // R270

constexpr Point srs_i_offsets[NUM_ROTATIONS][NUM_TRIALS]{
    {{0, 0}, {-1, 0}, {2, 0}, {-1, 0}, {2, 0}},     // R0
    {{-1, 0}, {0, 0}, {0, 0}, {0, -1}, {1, 2}},     // R90
    {{-1, -1}, {1, -1}, {-2, -1}, {1, 0}, {-2, 0}}, // R180
    {{0, -1}, {0, -1}, {0, -1}, {0, 1}, {0, -2}}};  // R270

void srs_rotation(Tetromino &tet, void (Tetromino::*rotation_func)(),
                  const Matrix &matrix) {
  const auto &offsets =
      tet.type() == Tetromino::I ? srs_i_offsets : srs_offsets;
  Tetromino::Rotation curr, prev = tet.rotation();
  Point orignal_pos = tet.pos();

  (tet.*rotation_func)();
  curr = tet.rotation();

  for (std::size_t t = 0; t < NUM_TRIALS; ++t) {
    Point kick = offsets[prev][t] - offsets[curr][t];
    tet.shift(kick);

    if (std::ranges::all_of(tet.shape(), Matrix::IsPosValid(matrix)))
      return;
  }

  tet.set_pos(orignal_pos);
}
} // namespace

void srs::rotate_cw(Tetromino &tet, const Matrix &matrix) {
  if (tet.type() != Tetromino::O) {
    srs_rotation(tet, &Tetromino::rotate_cw, matrix);
  }
}

void srs::rotate_ccw(Tetromino &tet, const Matrix &matrix) {
  if (tet.type() != Tetromino::O) {
    srs_rotation(tet, &Tetromino::rotate_ccw, matrix);
  }
}
