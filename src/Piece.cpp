#include "Piece.hpp"
#include "Geometry.hpp"
#include "Playfield.hpp"
#include <cstddef>

Piece::Piece(Type type, Point pos)
    : type(type), rotation(Rotation::r0), pos(pos) {
  static constexpr Vector SHAPE_OFFSETS[7][4]{
      {{-1, 0}, {0, 0}, {1, 0}, {2, 0}},   // I
      {{0, -1}, {0, 0}, {1, 0}, {1, -1}},  // O
      {{-1, 0}, {0, 0}, {0, -1}, {1, 0}},  // T
      {{-1, 0}, {0, 0}, {0, -1}, {1, -1}}, // S
      {{-1, -1}, {0, -1}, {0, 0}, {1, 0}}, // Z
      {{-1, -1}, {-1, 0}, {0, 0}, {1, 0}}, // J
      {{-1, 0}, {0, 0}, {1, 0}, {1, -1}},  // L
  };

  for (size_t i = 0; i < 4; ++i)
    shape[i] = pos + SHAPE_OFFSETS[static_cast<size_t>(type)][i];
}

auto Piece::shift(Vector delta, const Playfield &playfield) -> bool {
  auto test_shape = shape;
  for (auto &p : test_shape)
    p += delta;
  if (playfield.can_place(test_shape)) {
    pos += delta;
    shape = test_shape;
    return true;
  }
  return false;
}

auto Piece::rotate(RotationDir dir, const Playfield &playfield) -> bool {
  if (type == Type::O)
    return false;

  // SRS offset data
  static constexpr Vector STANDARD_PIECE_OFFSETS[4][5]{
      {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},       // R0
      {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},     // R90
      {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},       // R180
      {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}}; // R270

  static constexpr Vector I_PIECE_OFFSETS[4][5]{
      {{0, 0}, {-1, 0}, {2, 0}, {-1, 0}, {2, 0}},     // R0
      {{-1, 0}, {0, 0}, {0, 0}, {0, -1}, {0, 2}},     // R90
      {{-1, -1}, {1, -1}, {-2, -1}, {1, 0}, {-2, 0}}, // R180
      {{0, -1}, {0, -1}, {0, -1}, {0, 1}, {0, -2}}};  // R270

  const auto &offsets =
      type == Piece::Type::I ? I_PIECE_OFFSETS : STANDARD_PIECE_OFFSETS;

  auto test = *this;
  test.rotate_unchecked(dir);
  const auto from = static_cast<size_t>(rotation);
  const auto to = static_cast<size_t>(test.rotation);

  for (size_t i = 0; i < 5; ++i) {
    const auto offset = offsets[from][i] - offsets[to][i];
    if (test.shift(offset, playfield)) {
      *this = test;
      return true;
    }
  }
  return false;
}

void Piece::hard_drop(const Playfield &playfield) {
  while (shift({0, 1}, playfield)) {
  }
}

void Piece::shift_unchecked(Vector delta) {
  pos += delta;
  for (auto &p : shape)
    p += delta;
}

void Piece::rotate_unchecked(RotationDir dir) {
  if (type == Type::O)
    return;

  rotation = static_cast<Rotation>(
      (static_cast<int>(rotation) + static_cast<int>(dir)) % 4);
  switch (dir) {
  case RotationDir::Clockwise:
    for (auto &p : shape) {
      const auto delta = p - pos;
      p.x = pos.x - delta.y;
      p.y = pos.y + delta.x;
    }
    break;
  case RotationDir::Counterclockwise:
    for (auto &p : shape) {
      const auto delta = p - pos;
      p.x = pos.x + delta.y;
      p.y = pos.y - delta.x;
    }
    break;
  }
}

void Piece::set_pos(Point position) {
  const auto delta = position - pos;
  pos = position;
  for (auto &p : shape)
    p += delta;
}

auto Piece::get_type() const -> Type { return type; }

auto Piece::get_rotation() const -> Rotation { return rotation; }

auto Piece::get_pos() const -> Point { return pos; }

auto Piece::get_shape() const -> const Shape & { return shape; }
