#pragma once
#include "Point.hpp"
#include <array>
#include <cstdint>

class Matrix;

struct Tetromino {
  using Shape = std::array<Point<int>, 4>;
  enum class Type : uint8_t { I = 0, O = 1, T = 2, S = 3, Z = 4, J = 5, L = 6 };
  enum class Rotation : uint8_t { R0 = 0, R90 = 1, R180 = 2, R270 = 3 };

  Type type = Type::I;
  Point<int> pos{};
  Rotation rotation = Rotation::R0;
};

namespace tetromino {
auto shape_at(Tetromino tetromino, Point<int> pos) -> Tetromino::Shape;

auto cw_rotation(Tetromino tetromino) -> Tetromino;

auto ccw_rotation(Tetromino tetromino) -> Tetromino;

auto half_rotation(Tetromino tetromino) -> Tetromino;

auto local_shift(Tetromino &piece, Point<int> delta, const Matrix &matrix)
    -> bool;

void hard_drop(Tetromino &piece, const Matrix &matrix);

void srs_rotation(Tetromino &tet, Tetromino rotated, const Matrix &matrix);
} // namespace tetromino
