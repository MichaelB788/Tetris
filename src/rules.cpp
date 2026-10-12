#include "rules.hpp"
#include "FPoint.hpp"
#include "Matrix.hpp"
#include "Piece.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>

auto piece_query::is_valid_shape(const Piece::Shape &shape,
                                 const Matrix &matrix) -> bool {
  return std::all_of(shape.cbegin(), shape.cend(),
                     [&](auto pos) { return matrix.is_fpos_valid_at(pos); });
}

auto piece_query::is_shape_within_bounds(const Piece::Shape &shape) -> bool {
  return std::all_of(shape.cbegin(), shape.cend(),
                     Matrix::is_fpos_within_bounds);
}

auto piece_action::hard_drop(Piece pc, const Matrix &matrix) -> Piece {
  auto test = pc;
  ++test.pos.y;
  while (piece_query::is_valid_shape(test.get_shape(), matrix)) {
    ++test.pos.y;
    ++pc.pos.y;
  }
  return pc;
}

auto piece_action::shift(Piece pc, FPoint delta, const Matrix &matrix)
    -> std::optional<Piece> {
  pc.pos = fpoint::add(pc.pos, delta);
  return piece_query::is_valid_shape(pc.get_shape(), matrix)
             ? std::make_optional(pc)
             : std::nullopt;
}

auto piece_action::srs_rotation(Piece piece, Piece::Rotation dir,
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

  const auto rotated_piece =
      Piece{.type = piece.type,
            .rotation = static_cast<Piece::Rotation>(
                (static_cast<int>(piece.rotation) + static_cast<int>(dir)) % 4),
            .pos = piece.pos};
  const auto from = static_cast<size_t>(piece.rotation);
  const auto to = static_cast<size_t>(rotated_piece.rotation);

  for (size_t i = 0; i < 5; ++i) {
    const auto offset = fpoint::subtract(offsets[from][i], offsets[to][i]);
    if (auto new_piece = piece_action::shift(rotated_piece, offset, matrix))
      return new_piece;
  }

  return std::nullopt;
}

void piece_action::lock_down(Piece pc, Matrix &matrix) {
  const auto shape = pc.get_shape();
  assert(piece_query::is_valid_shape(shape, matrix));
  for (const auto pos : shape)
    matrix.at(pos) = pc.type;
}
