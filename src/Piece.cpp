#include "Piece.hpp"
#include "Matrix.hpp"
#include "Point.hpp"
#include <cstddef>
#include <optional>
#include <utility>

auto piece::create_shape(Piece pc) -> Piece::Shape {
  // Piece shape/rotation data
  static constexpr Piece::Shape SHAPES[7][4]{
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

  auto shape =
      SHAPES[std::to_underlying(pc.type)][std::to_underlying(pc.rotation)];
  for (auto &pos : shape)
    pos = fpoint::add(pos, pc.pos);
  return shape;
}

auto piece::shift(Piece pc, FPoint delta) -> Piece {
  pc.pos = fpoint::add(pc.pos, delta);
  return pc;
}

auto piece::rotate(Piece pc, Piece::Rotation dir) -> Piece {
  pc.rotation = static_cast<Piece::Rotation>(
      (std::to_underlying(pc.rotation) + std::to_underlying(dir)) % 4);
  return pc;
}

auto piece::hard_drop(Piece pc, const Matrix &matrix) -> Piece {
  auto test = pc;
  ++test.pos.y;
  while (matrix.can_place(piece::create_shape(test))) {
    ++test.pos.y;
    ++pc.pos.y;
  }
  return pc;
}

auto piece::shift_within(Piece pc, FPoint delta, const Matrix &matrix)
    -> std::optional<Piece> {
  pc.pos = fpoint::add(pc.pos, delta);
  return matrix.can_place(piece::create_shape(pc)) ? std::make_optional(pc)
                                                   : std::nullopt;
}

auto piece::rotate_srs(Piece pc, Piece::Rotation next, const Matrix &matrix)
    -> std::optional<Piece> {
  // SRS offset data
  static constexpr FPoint STANDARD_PIECE_OFFSETS[4][5]{
      {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},       // R0
      {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},     // R90
      {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},       // R180
      {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}}; // R270

  static constexpr FPoint I_PIECE_OFFSETS[4][5]{
      {{0, 0}, {-1, 0}, {2, 0}, {-1, 0}, {2, 0}},     // R0
      {{-1, 0}, {0, 0}, {0, 0}, {0, -1}, {0, 2}},     // R90
      {{-1, -1}, {1, -1}, {-2, -1}, {1, 0}, {-2, 0}}, // R180
      {{0, -1}, {0, -1}, {0, -1}, {0, 1}, {0, -2}}};  // R270

  const auto &offsets =
      pc.type == Piece::Type::I ? I_PIECE_OFFSETS : STANDARD_PIECE_OFFSETS;

  const auto rotated_pc = piece::rotate(pc, next);
  const auto from = std::to_underlying(pc.rotation);
  const auto to = std::to_underlying(rotated_pc.rotation);
  for (size_t i = 0; i < 5; ++i) {
    const auto test = piece::shift(
        rotated_pc, fpoint::subtract(offsets[from][i], offsets[to][i]));
    if (matrix.can_place(piece::create_shape(test)))
      return test;
  }
  return std::nullopt;
}
