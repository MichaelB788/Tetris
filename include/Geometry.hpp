#pragma once

struct Vector {
  float x, y;

  auto operator*=(float scalar) -> Vector &;

  [[nodiscard]] auto operator*(float scalar) const -> Vector;
};

struct Point {
  float x, y;

  [[nodiscard]] auto is_between(Point min, Point max) const -> bool;

  auto operator+=(Vector v) -> Point &;
  auto operator-=(Vector v) -> Point &;

  [[nodiscard]] auto operator+(Vector v) const -> Point;
  [[nodiscard]] auto operator-(Vector v) const -> Point;
};

struct Size {
  float w, h;
};
