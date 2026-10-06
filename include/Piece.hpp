#pragma once
#include "Point.hpp"
#include <array>
#include <cstdint>
#include <optional>

class Matrix;

struct Piece {
  using Shape = std::array<FPoint, 4>;

  enum class Type : uint8_t { I = 0, O = 1, T = 2, S = 3, Z = 4, J = 5, L = 6 };
  enum class Rotation : uint8_t {
    Default = 0,
    Clockwise = 1,
    Half = 2,
    Counterclockwise = 3
  };

  Type type{};
  FPoint pos{};
  Rotation rotation{};
};

namespace piece {
[[nodiscard]] auto create_shape(Piece pc) -> Piece::Shape;

[[nodiscard]] auto shift(Piece pc, FPoint delta) -> Piece;
[[nodiscard]] auto rotate(Piece pc, Piece::Rotation dir) -> Piece;
[[nodiscard]] auto hard_drop(Piece pc, const Matrix &matrix) -> Piece;

[[nodiscard]] auto shift_within(Piece pc, FPoint delta, const Matrix &matrix)
    -> std::optional<Piece>;
[[nodiscard]] auto rotate_srs(Piece pc, Piece::Rotation next,
                              const Matrix &matrix) -> std::optional<Piece>;
} // namespace piece
