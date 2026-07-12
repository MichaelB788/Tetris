#pragma once
#include "Point.hpp"
#include <array>
#include <cstdint>

class Matrix;

class Tetromino {
public:
  using Shape = std::array<Point<int>, 4>;
  enum class Type : uint8_t { I = 0, O = 1, T = 2, S = 3, Z = 4, J = 5, L = 6 };
  enum class Rotation : uint8_t { R0 = 0, R90 = 1, R180 = 2, R270 = 3 };

  Tetromino(Type t, Point<int> p = {0, 0}, Rotation r = Rotation::R0)
      : type_(t), pos_(p), rotation_(r) {}

  void shift(Point<int> delta);
  void set_pos(Point<int> pos);
  auto local_shift(Point<int> delta, const Matrix &matrix) -> bool;
  void hard_drop(const Matrix &matrix);

  void rotate_cw();
  void rotate_ccw();
  void rotate_half();

  void srs_rotate_cw(const Matrix &matrix);
  void srs_rotate_ccw(const Matrix &matrix);
  void srs_rotate_half(const Matrix &matrix);

  auto get_shape_at(Point<int> pos) const -> Shape;
  auto get_shifted_shape(Point<int> delta) const -> Shape;
  auto get_shape() const -> Shape;

  auto get_pos_after_hard_drop(const Matrix &matrix) const -> Point<int>;

  auto get_type() const -> Type;
  auto get_pos() const -> Point<int>;
  auto get_rotation() const -> Rotation;

private:
  auto n_clockwise_rotations(unsigned n) const -> Rotation;
  void srs_rotation(Rotation next_rotation, const Matrix &matrix);

  Type type_ = Type::I;
  Point<int> pos_{};
  Rotation rotation_ = Rotation::R0;
};
