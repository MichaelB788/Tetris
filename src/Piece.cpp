#include "Piece.hpp"
#include "Geometry.hpp"
#include <algorithm>
#include <cstddef>

Piece::Piece(Type type, Point pos, Rotation rotation)
    : type(type), rotation(rotation), pos(pos) {
  static constexpr Vector SHAPE_OFFSETS[7][4]{
      {{-1, 0}, {0, 0}, {1, 0}, {2, 0}},   // I
      {{0, -1}, {0, 0}, {1, 0}, {1, -1}},  // O
      {{-1, 0}, {0, 0}, {0, -1}, {1, 0}},  // T
      {{-1, 0}, {0, 0}, {0, -1}, {1, -1}}, // S
      {{-1, -1}, {0, -1}, {0, 0}, {1, 0}}, // Z
      {{-1, 0}, {0, 0}, {1, 0}, {1, -1}},  // J
      {{-1, -1}, {-1, 0}, {0, 0}, {1, 0}}  // L
  };

  for (size_t i = 0; i < 4; ++i)
    shape[i] = pos + SHAPE_OFFSETS[static_cast<size_t>(type)][i];
}

auto Piece::shift(Vector delta, Rectangle bounds) -> bool {
  auto test = *this;
  test.shift_unbounded(delta);
  if (std::all_of(test.shape.cbegin(), test.shape.cend(),
                  [bounds](Point p) { return p.is_within(bounds); })) {
    *this = test;
    return true;
  }
  return false;
}

auto Piece::rotate(RotationDir dir, Rectangle bounds) -> bool {
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
  test.rotate_unbounded(dir);
  const auto from = static_cast<size_t>(rotation);
  const auto to = static_cast<size_t>(test.rotation);

  for (size_t i = 0; i < 5; ++i) {
    const auto offset = offsets[from][i] - offsets[to][i];
    if (test.shift(offset, bounds)) {
      *this = test;
      return true;
    }
  }
  return false;
}

void Piece::hard_drop(Rectangle bounds) {
  auto test = *this;
  auto delta = Vector{};
  while (test.shift({0, 1}, bounds))
    ++delta.y;
  shift_unbounded(delta);
}

void Piece::shift_unbounded(Vector delta) {
  pos += delta;
  for (auto &p : shape)
    p += delta;
}

void Piece::rotate_unbounded(RotationDir dir) {
  rotation = static_cast<Rotation>(static_cast<unsigned>(rotation) +
                                   static_cast<unsigned>(dir) % 4);
  switch (dir) {
  case RotationDir::Clockwise:
    for (auto &p : shape) {
      const auto delta = p - pos;
      p.x = pos.x + delta.y;
      p.y = pos.y - delta.x;
    }
    break;
  case RotationDir::Counterclockwise:
    for (auto &p : shape) {
      const auto delta = p - pos;
      p.x = pos.x - delta.y;
      p.y = pos.y + delta.x;
    }
    break;
  }
}

auto Piece::get_type() const -> Type { return type; }

auto Piece::get_rotation() const -> Rotation { return rotation; }

auto Piece::get_pos() const -> Point { return pos; }

auto Piece::get_shape() const -> const Shape & { return shape; }
