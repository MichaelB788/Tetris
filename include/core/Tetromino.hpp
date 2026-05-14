#pragma once
#include "util/Point.hpp"
#include <array>
#include <cstdint>

struct Tetromino {
  using Shape = std::array<Point<int>, 4>;
  enum Type : uint8_t { I = 0, O, T, S, Z, J, L };
  enum Rotation : uint8_t { R0, R90, R180, R270 };

  Type type = I;
  Point<int> pos{};
  Rotation rotation = R0;
};

namespace tetromino {
auto shape_of(Tetromino tetromino) -> Tetromino::Shape;

auto shape_at(Tetromino tetromino, Point<int> pos) -> Tetromino::Shape;

auto rotated_clockwise(Tetromino tetromino) -> Tetromino;

auto rotated_counterclockwise(Tetromino tetromino) -> Tetromino;

auto rotated_half_turn(Tetromino tetromino) -> Tetromino;
} // namespace tetromino
