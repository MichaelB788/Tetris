#include "rules.hpp"
#include "FPoint.hpp"
#include "Piece.hpp"

auto piece_action::hard_drop(Piece pc, const Matrix &matrix) -> Piece {
  auto test = pc;
  ++test.pos.y;
  while (matrix.is_shape_valid(test.get_shape())) {
    ++test.pos.y;
    ++pc.pos.y;
  }
  return pc;
}

auto piece_action::shift(Piece pc, FPoint delta, const Matrix &matrix)
    -> std::optional<Piece> {
  pc.pos = fpoint::add(pc.pos, delta);
  return matrix.is_shape_valid(pc.get_shape()) ? std::make_optional(pc)
                                               : std::nullopt;
}

auto piece_action::srs_rotation(Piece piece, Piece::Rotation next,
                                const Matrix &matrix) -> std::optional<Piece> {
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
      piece.type == Piece::Type::I ? I_PIECE_OFFSETS : STANDARD_PIECE_OFFSETS;

  const auto from = static_cast<int>(piece.rotation);
  const auto to = static_cast<int>(next);
  auto rotated_piece = piece;
  rotated_piece.rotation = static_cast<Piece::Rotation>(from + to % 4);

  for (size_t i = 0; i < 5; ++i) {
    const auto wallkick = fpoint::subtract(offsets[from][i], offsets[to][i]);
    rotated_piece.pos = fpoint::add(rotated_piece.pos, wallkick);
    if (matrix.is_shape_valid(rotated_piece.get_shape()))
      return rotated_piece;
    else
      rotated_piece.pos = piece.pos;
  }
  return std::nullopt;
}
