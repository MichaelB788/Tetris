#include "Tetromino.hpp"
#include "Matrix.hpp"
#include "Point.hpp"
#include <cstddef>

namespace {
// Tetromino shape/rotation data
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
    {{{{-1, 0}, {0, 0}, {1, 0}, {1, -1}}},    // R0
     {{{0, -1}, {0, 0}, {0, 1}, {1, 1}}},     // R90
     {{{-1, 0}, {0, 0}, {1, 0}, {-1, 1}}},    // R180
     {{{0, -1}, {0, 0}, {0, 1}, {-1, -1}}}}}; // R270

// SRS offset data
constexpr Point<int> STANDARD_PIECE_OFFSETS[4][5]{
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},       // R0
    {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},     // R90
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},       // R180
    {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}}; // R270

constexpr Point<int> I_PIECE_OFFSETS[4][5]{
    {{0, 0}, {-1, 0}, {2, 0}, {-1, 0}, {2, 0}},     // R0
    {{-1, 0}, {0, 0}, {0, 0}, {0, -1}, {0, 2}},     // R90
    {{-1, -1}, {1, -1}, {-2, -1}, {1, 0}, {-2, 0}}, // R180
    {{0, -1}, {0, -1}, {0, -1}, {0, 1}, {0, -2}}};  // R270
} // namespace

void Tetromino::set_pos(Point<int> pos) { pos = pos; }

void Tetromino::set_rotation(Rotation r) { rotation = r; }

void Tetromino::shift(Point<int> delta) { pos += delta; }

auto Tetromino::try_shift(Point<int> delta, const Matrix &matrix) -> bool {
  if (matrix.is_move_valid(get_shifted_shape(delta))) {
    pos += delta;
    return true;
  }
  return false;
}

void Tetromino::hard_drop(const Matrix &matrix) {
  pos = get_pos_after_hard_drop(matrix);
}

auto Tetromino::srs_rotation(Rotation next_rotation, const Matrix &matrix)
    -> bool {
  const auto &offsets =
      type == Type::I ? I_PIECE_OFFSETS : STANDARD_PIECE_OFFSETS;

  const Tetromino rotated{type, pos, next_rotation};
  const auto from = static_cast<size_t>(rotation);
  const auto to = static_cast<size_t>(next_rotation);
  for (size_t i = 0; i < 5; ++i) {
    const auto wall_kick = offsets[from][i] - offsets[to][i];
    if (matrix.is_move_valid(rotated.get_shifted_shape(wall_kick))) {
      rotation = next_rotation;
      pos += wall_kick;
      return true;
    }
  }
  return true;
}

auto Tetromino::get_shape_at(Point<int> pos) const -> Shape {
  const auto t = static_cast<size_t>(type);
  const auto r = static_cast<size_t>(rotation);
  auto ret = SHAPES[t][r];
  for (auto &p : ret) {
    p += pos;
  }
  return ret;
}

auto Tetromino::get_shifted_shape(Point<int> delta) const -> Shape {
  return get_shape_at(pos + delta);
}

auto Tetromino::get_shape() const -> Shape { return get_shape_at(pos); }

auto Tetromino::get_pos_after_hard_drop(const Matrix &matrix) const
    -> Point<int> {
  Point<int> drop_pos = pos;
  Point<int> test_pos = pos + Point{.y = 1};
  while (matrix.is_move_valid(get_shape_at(test_pos))) {
    ++test_pos.y;
    ++drop_pos.y;
  }
  return drop_pos;
}

auto Tetromino::get_type() const -> Type { return type; }

auto Tetromino::get_pos() const -> Point<int> { return pos; }

auto Tetromino::get_rotation() const -> Rotation { return rotation; }

auto tetromino::rotated_cw(Tetromino::Rotation from, unsigned n)
    -> Tetromino::Rotation {
  const auto r = static_cast<uint8_t>(from);
  return static_cast<Tetromino::Rotation>((r + n) % 4);
}
