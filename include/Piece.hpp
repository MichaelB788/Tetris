#pragma once
#include "Geometry.hpp"
#include <array>
#include <cstdint>

class Playfield;

class Piece {
public:
  using Shape = std::array<Point, 4>;

  enum class Type : uint8_t { I, O, T, S, Z, J, L };
  enum class Rotation : uint8_t { r0, r90, r180, r270 };
  enum class RotationDir { Clockwise = 1, Counterclockwise = 3 };

  Piece(Type type = Type::I, Point pos = {0, 0});

  auto shift(Vector delta, const Playfield &playfield) -> bool;
  auto rotate(RotationDir dir, const Playfield &playfield) -> bool;
  void hard_drop(const Playfield &playfield);

  void shift_unchecked(Vector delta);
  void rotate_unchecked(RotationDir dir);

  void set_pos(Point position);

  [[nodiscard]] auto get_type() const -> Type;
  [[nodiscard]] auto get_rotation() const -> Rotation;
  [[nodiscard]] auto get_pos() const -> Point;
  [[nodiscard]] auto get_shape() const -> const Shape &;

private:
  Type type{};
  Rotation rotation{};
  Point pos{};
  Shape shape{};
};
