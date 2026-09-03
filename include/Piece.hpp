#pragma once
#include "Point.hpp"
#include <array>
#include <cstdint>

class Matrix;

struct Piece {
  using Shape = std::array<FPoint, 4>;

  enum class MoveResult { Applied, Unapplied };
  enum class Type : uint8_t { I = 0, O = 1, T = 2, S = 3, Z = 4, J = 5, L = 6 };
  enum class Rotation : uint8_t { Default = 0, CW = 1, Half = 2, CCW = 3 };

  Type type;
  FPoint pos;
  Rotation rotation;
};

namespace piece {
[[nodiscard]] auto create_shape(Piece pc) -> Piece::Shape;

[[nodiscard]] auto shift(Piece pc, FPoint delta) -> Piece;
[[nodiscard]] auto rotate(Piece pc, Piece::Rotation dir) -> Piece;

void hard_drop(Piece &pc, const Matrix &matrix);
[[nodiscard]] auto shift_within(Piece &pc, FPoint delta, const Matrix &matrix)
    -> Piece::MoveResult;
[[nodiscard]] auto rotate_srs(Piece &pc, Piece::Rotation next,
                              const Matrix &matrix) -> Piece::MoveResult;
} // namespace piece
