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
    {{{{-1, 0}, {0, 0}, {1, 0}, {1, -1}}},  // R0
     {{{0, -1}, {0, 0}, {0, 1}, {1, 1}}},   // R90
     {{{-1, 0}, {0, 0}, {1, 0}, {-1, 1}}},  // R180
     {{{0, -1}, {0, 0}, {0, 1}, {-1, -1}}}} // R270
};

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

void Tetromino::shift(Point<int> delta) { pos_ += delta; }

void Tetromino::set_pos(Point<int> pos) { pos_ = pos; }

auto Tetromino::try_shift(Point<int> delta, const Matrix &matrix) -> bool {
  if (matrix.is_move_valid(get_shifted_shape(delta))) {
    pos_ += delta;
    return true;
  }
  return false;
}

void Tetromino::hard_drop(const Matrix &matrix) {
  pos_ = get_pos_after_hard_drop(matrix);
}

void Tetromino::rotate_cw() { rotation_ = n_clockwise_rotations(1); }

void Tetromino::rotate_ccw() { rotation_ = n_clockwise_rotations(3); }

void Tetromino::rotate_half() { rotation_ = n_clockwise_rotations(2); }

void Tetromino::srs_rotate_cw(const Matrix &matrix) {
  srs_rotation(n_clockwise_rotations(1), matrix);
}

void Tetromino::srs_rotate_ccw(const Matrix &matrix) {
  srs_rotation(n_clockwise_rotations(3), matrix);
}

void Tetromino::srs_rotate_half(const Matrix &matrix) {
  srs_rotation(n_clockwise_rotations(2), matrix);
}

auto Tetromino::get_shape_at(Point<int> pos) const -> Shape {
  const auto t = static_cast<size_t>(type_);
  const auto r = static_cast<size_t>(rotation_);
  auto ret = SHAPES[t][r];
  for (auto &p : ret) {
    p += pos;
  }
  return ret;
}

auto Tetromino::get_shifted_shape(Point<int> delta) const -> Shape {
  return get_shape_at(pos_ + delta);
}

auto Tetromino::get_shape() const -> Shape { return get_shape_at(pos_); }

auto Tetromino::get_pos_after_hard_drop(const Matrix &matrix) const
    -> Point<int> {
  Point<int> drop_pos = pos_;
  Point<int> test_pos = pos_ + Point{.y = 1};
  while (matrix.is_move_valid(get_shape_at(test_pos))) {
    ++test_pos.y;
    ++drop_pos.y;
  }
  return drop_pos;
}

auto Tetromino::get_type() const -> Type { return type_; }

auto Tetromino::get_pos() const -> Point<int> { return pos_; }

auto Tetromino::get_rotation() const -> Rotation { return rotation_; }

auto Tetromino::n_clockwise_rotations(unsigned n) const -> Rotation {
  const auto curr = static_cast<uint8_t>(rotation_);
  return static_cast<Rotation>((curr + n) % 4);
}

void Tetromino::srs_rotation(Rotation next_rotation, const Matrix &matrix) {
  const auto &offsets =
      type_ == Type::I ? I_PIECE_OFFSETS : STANDARD_PIECE_OFFSETS;

  const Tetromino rotated{type_, pos_, next_rotation};
  const auto from = static_cast<size_t>(rotation_);
  const auto to = static_cast<size_t>(next_rotation);
  for (size_t i = 0; i < 5; ++i) {
    const auto wall_kick = offsets[from][i] - offsets[to][i];
    if (matrix.is_move_valid(rotated.get_shifted_shape(wall_kick))) {
      rotation_ = next_rotation;
      pos_ += wall_kick;
      return;
    }
  }
}
