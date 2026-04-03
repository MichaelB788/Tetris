#pragma once
#include "util/CircularIntegral.hpp"
#include "util/Point.hpp"
#include <array>
#include <cstddef>
#include <cstdint>

struct Tetromino {
  static constexpr size_t MAX_TETROMINO = 7;
  static constexpr size_t MAX_ROTATIONS = 4;

  enum Type : uint8_t { I = 0, O, T, S, Z, J, L };

  using Shape = std::array<Point, 4>;
  using Rotation = CircularIntegral<uint8_t, MAX_ROTATIONS>;

  Type type = Type::I;

  Point pos = {.x = 0, .y = 0};

  Rotation rotation = 0;

  [[nodiscard]] Shape shifted(Point delta) const;

  [[nodiscard]] Shape shape() const;
};
