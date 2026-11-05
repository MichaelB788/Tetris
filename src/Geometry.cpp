#include "Geometry.hpp"

auto Vector::operator*=(float scalar) -> Vector & {
  x *= scalar;
  y *= scalar;
  return *this;
}

auto Vector::operator*(float scalar) const -> Vector {
  return {x * scalar, y * scalar};
}

auto Point::is_between(Point min, Point max) const -> bool {
  return x >= min.x && y >= min.y && x <= max.x && y <= max.y;
}

auto Point::operator+=(Vector v) -> Point & {
  x += v.x;
  y += v.y;
  return *this;
}

auto Point::operator-=(Vector v) -> Point & {
  x -= v.x;
  y -= v.y;
  return *this;
}

auto Point::operator+(Vector v) const -> Point { return {x + v.x, y + v.y}; }

auto Point::operator-(Vector v) const -> Point { return {x - v.x, y - v.y}; }
