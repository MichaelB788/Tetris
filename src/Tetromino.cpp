#include "Tetromino.hpp"
#include "Matrix.hpp"
#include "Point.hpp"
#include <array>
#include <cstddef>

namespace {
constexpr Tetromino::Shape SHAPES[7][4]{
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

auto n_clockwise_rotations(Tetromino t, unsigned n) -> Tetromino {
  const auto r = static_cast<unsigned>(t.rotation);
  return Tetromino{.type = t.type,
                   .pos = t.pos,
                   .rotation = static_cast<Tetromino::Rotation>((r + n) % 4)};
}
} // namespace

auto tetromino::shape_at(Tetromino tetromino, Point<int> pos)
    -> Tetromino::Shape {
  const auto t = static_cast<size_t>(tetromino.type);
  const auto r = static_cast<size_t>(tetromino.rotation);
  auto ret = SHAPES[t][r];
  for (auto &p : ret)
    p += pos;
  return ret;
}

auto tetromino::cw_rotation(Tetromino tetromino) -> Tetromino {
  return n_clockwise_rotations(tetromino, 1);
}

auto tetromino::ccw_rotation(Tetromino tetromino) -> Tetromino {
  return n_clockwise_rotations(tetromino, 3);
}

auto tetromino::half_rotation(Tetromino tetromino) -> Tetromino {
  return n_clockwise_rotations(tetromino, 2);
}

auto tetromino::local_shift(Tetromino &piece, Point<int> delta,
                            const Matrix &matrix) -> bool {
  const auto shifted_pos = piece.pos + delta;
  if (matrix.is_move_valid(tetromino::shape_at(piece, shifted_pos))) {
    piece.pos = shifted_pos;
    return true;
  }
  return false;
}

void tetromino::hard_drop(Tetromino &piece, const Matrix &matrix) {
  auto new_pos = piece.pos;
  auto test_pos = new_pos + Point{.y = 1};
  while (matrix.is_move_valid(tetromino::shape_at(piece, test_pos))) {
    ++test_pos.y;
    ++new_pos.y;
  }
  piece.pos = new_pos;
}

void tetromino::srs_rotation(Tetromino &current, Tetromino rotated,
                             const Matrix &matrix) {
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
  const auto &offsets = current.type == Tetromino::Type::I
                            ? I_PIECE_OFFSETS
                            : STANDARD_PIECE_OFFSETS;

  const auto from = static_cast<size_t>(current.rotation);
  const auto to = static_cast<size_t>(rotated.rotation);
  for (size_t i = 0; i < 5; ++i) {
    const auto wall_kick = offsets[from][i] - offsets[to][i];
    const auto test_pos = rotated.pos + wall_kick;
    if (matrix.is_move_valid(tetromino::shape_at(rotated, test_pos))) {
      current.rotation = rotated.rotation;
      current.pos = test_pos;
      return;
    }
  }
}
