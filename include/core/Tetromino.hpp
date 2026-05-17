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

auto shape_of(Tetromino tetromino) -> Tetromino::Shape;

auto shape_at(Tetromino tetromino, Point<int> pos) -> Tetromino::Shape;

auto clockwise_rotation(Tetromino tetromino) -> Tetromino;

auto counterclockwise_rotation(Tetromino tetromino) -> Tetromino;

auto half_turn_rotation(Tetromino tetromino) -> Tetromino;

class Matrix;

auto local_shift(Tetromino &piece, Point<int> delta, const Matrix &matrix)
    -> bool;

void hard_drop(Tetromino &piece, const Matrix &matrix);

enum class RotationDir { Clockwise, CounterClockwise, HalfTurn };
void srs_rotation(Tetromino &tet, RotationDir dir, const Matrix &matrix);
