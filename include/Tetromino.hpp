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
      : type(t), pos(p), rotation(r) {}

  void set_pos(Point<int> pos);
  void set_rotation(Rotation r);

  void shift(Point<int> delta);
  auto try_shift(Point<int> delta, const Matrix &matrix) -> bool;
  void hard_drop(const Matrix &matrix);

  auto srs_rotation(Rotation next_rotation, const Matrix &matrix) -> bool;

  [[nodiscard]] auto get_shape_at(Point<int> pos) const -> Shape;
  [[nodiscard]] auto get_shifted_shape(Point<int> delta) const -> Shape;
  [[nodiscard]] auto get_shape() const -> Shape;

  [[nodiscard]] auto get_pos_after_hard_drop(const Matrix &matrix) const
      -> Point<int>;

  [[nodiscard]] auto get_type() const -> Type;
  [[nodiscard]] auto get_pos() const -> Point<int>;
  [[nodiscard]] auto get_rotation() const -> Rotation;

private:
  Type type = Type::I;
  Point<int> pos{};
  Rotation rotation = Rotation::R0;
};

namespace tetromino {
auto rotated_cw(Tetromino::Rotation from, unsigned n) -> Tetromino::Rotation;
}
