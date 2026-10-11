#pragma once
#include "FPoint.hpp"
#include <array>
#include <cstdint>

struct Piece {
  using Shape = std::array<FPoint, 4>;

  enum class Type : uint8_t { I = 0, O = 1, T = 2, S = 3, Z = 4, J = 5, L = 6 };
  enum class Rotation : uint8_t { r0 = 0, r90 = 1, r180 = 2, r270 = 3 };

  [[nodiscard]] auto get_shape() const -> Piece::Shape;

  Type type{};
  FPoint pos{};
  Rotation rotation{};
};
