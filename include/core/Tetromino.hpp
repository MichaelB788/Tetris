#pragma once
#include "util/CircularUint.hpp"
#include "util/Point.hpp"
#include <array>
#include <cstdint>

struct Tetromino {
  using Shape = std::array<Point, 4>;
  using Rotation = CircularUint<uint8_t, 4>;

  enum Type : uint8_t { I = 0, O, T, S, Z, J, L };

  Type type = Type::I;

  Point pos = {.x = 0, .y = 0};

  Rotation rotation = 0;

  [[nodiscard]] auto shifted(Point delta) const -> Shape;

  [[nodiscard]] auto shape() const -> Shape;

  [[nodiscard]] auto shape_at(Point p, Rotation r) const -> Shape;
};
