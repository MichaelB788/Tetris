#include "core/Tetromino.hpp"
#include "core/Matrix.hpp"
#include <array>

/**
 * All possible rotational states of each Tetromino. The data can be parsed via
 * the following pattern:
 *
 * SHAPES[TetrominoType][TetrominoRotation]
 */
static constexpr Tetromino::Shape SHAPES[7][4]{
    // I
    {{{{-1, 0}, {0, 0}, {1, 0}, {2, 0}}},   // R0
     {{{0, -1}, {0, 0}, {0, 1}, {0, 2}}},   // R90
     {{{-2, 0}, {-1, 0}, {0, 0}, {1, 0}}},  // R180
     {{{0, 1}, {0, 0}, {0, -1}, {0, -2}}}}, // R90

    // O
    {{{{0, 0}, {1, 0}, {0, -1}, {1, -1}}},  // R0
     {{{0, 0}, {1, 0}, {0, -1}, {1, -1}}},  // R90
     {{{0, 0}, {1, 0}, {0, -1}, {1, -1}}},  // R180
     {{{0, 0}, {1, 0}, {0, -1}, {1, -1}}}}, // R270

    // T
    {{{{-1, 0}, {0, 0}, {1, 0}, {0, -1}}},  // R0
     {{{0, 1}, {0, 0}, {0, -1}, {1, 0}}},   // R90
     {{{-1, 0}, {0, 0}, {1, 0}, {0, 1}}},   // R180
     {{{0, 1}, {0, 0}, {0, -1}, {-1, 0}}}}, // R270

    // S
    {{{{-1, 0}, {0, 0}, {0, -1}, {1, -1}}},  // R0
     {{{0, -1}, {0, 0}, {1, 0}, {1, 1}}},    // R90
     {{{-1, 1}, {0, 1}, {0, 0}, {1, 0}}},    // R180
     {{{-1, -1}, {-1, 0}, {0, 0}, {0, 1}}}}, // R270

    // Z
    {{{{-1, -1}, {0, -1}, {0, 0}, {1, 0}}},  // R0
     {{{0, 1}, {0, 0}, {1, 0}, {1, -1}}},    // R90
     {{{-1, 0}, {0, 0}, {0, 1}, {1, 1}}},    // R180
     {{{-1, 1}, {-1, 0}, {0, 0}, {0, -1}}}}, // R270

    // J
    {{{{-1, 0}, {0, 0}, {1, 0}, {-1, -1}}}, // R0
     {{{0, 1}, {0, 0}, {0, -1}, {1, -1}}},  // R90
     {{{-1, 0}, {0, 0}, {1, 0}, {1, 1}}},   // R180
     {{{0, 1}, {0, 0}, {0, -1}, {-1, 1}}}}, // R270

    // L
    {{{{-1, 0}, {0, 0}, {1, 0}, {1, -1}}},  // R0
     {{{0, -1}, {0, 0}, {0, 1}, {1, 1}}},   // R90
     {{{-1, 0}, {0, 0}, {1, 0}, {-1, 1}}},  // R180
     {{{0, -1}, {0, 0}, {0, 1}, {-1, -1}}}} // R270
};

auto shape_of(Tetromino tetromino) -> Tetromino::Shape {
  auto shape = SHAPES[tetromino.type][tetromino.rotation];
  for (auto &p : shape)
    p += tetromino.pos;
  return shape;
}

auto shape_at(Tetromino tetromino, Point<int> pos) -> Tetromino::Shape {
  auto shape = SHAPES[tetromino.type][tetromino.rotation];
  for (auto &p : shape)
    p += pos;
  return shape;
}

auto clockwise_rotation(Tetromino tetromino) -> Tetromino {
  tetromino.rotation =
      static_cast<Tetromino::Rotation>((tetromino.rotation + 1) % 4);
  return tetromino;
}

auto counterclockwise_rotation(Tetromino tetromino) -> Tetromino {
  tetromino.rotation =
      static_cast<Tetromino::Rotation>((tetromino.rotation + 3) % 4);
  return tetromino;
}

auto half_turn_rotation(Tetromino tetromino) -> Tetromino {
  tetromino.rotation =
      static_cast<Tetromino::Rotation>((tetromino.rotation + 2) % 4);
  return tetromino;
}

auto local_shift(Tetromino &piece, Point<int> delta, const Matrix &matrix)
    -> bool {
  if (matrix.is_move_valid(shape_at(piece, piece.pos + delta))) {
    piece.pos += delta;
    return true;
  }
  return false;
}

void hard_drop(Tetromino &piece, const Matrix &matrix) {
  int delta_y = 0;
  while (matrix.is_move_valid(
      shape_at(piece, piece.pos + Point{.y = delta_y + 1}))) {
    ++delta_y;
  }
  piece.pos.y += delta_y;
}

void srs_rotation(Tetromino &current, RotationDir dir, const Matrix &matrix) {
  /**
   * Offset data for all Tetromino. The data can be parsed via the following
   * pattern:
   *
   * PIECE_OFFSETS[TetrominoRotation][Trial]
   */
  static constexpr Point<int> STANDARD_PIECE_OFFSETS[4][5]{
      {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},       // R0
      {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},     // R90
      {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},       // R180
      {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}}; // R270
  static constexpr Point<int> I_PIECE_OFFSETS[4][5]{
      {{0, 0}, {-1, 0}, {2, 0}, {-1, 0}, {2, 0}},     // R0
      {{-1, 0}, {0, 0}, {0, 0}, {0, -1}, {0, 2}},     // R90
      {{-1, -1}, {1, -1}, {-2, -1}, {1, 0}, {-2, 0}}, // R180
      {{0, -1}, {0, -1}, {0, -1}, {0, 1}, {0, -2}}};  // R270

  Tetromino rotated;
  switch (dir) {
    using enum RotationDir;
  case Clockwise:
    rotated = clockwise_rotation(current);
    break;
  case CounterClockwise:
    rotated = counterclockwise_rotation(current);
    break;
  case HalfTurn:
    rotated = half_turn_rotation(current);
    break;
  }

  const auto &offsets =
      current.type == Tetromino::I ? I_PIECE_OFFSETS : STANDARD_PIECE_OFFSETS;
  const auto from = current.rotation, to = rotated.rotation;
  for (size_t i = 0; i < 5; ++i) {
    const Point kick = offsets[from][i] - offsets[to][i];
    if (matrix.is_move_valid(shape_at(rotated, rotated.pos + kick))) {
      rotated.pos += kick;
      current = rotated;
      return;
    }
  }
}
