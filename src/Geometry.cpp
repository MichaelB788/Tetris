#include "Geometry.hpp"

auto Vector::operator+=(Vector other) -> Vector & {
  x += other.x;
  y += other.y;
  return *this;
}

auto Vector::operator-=(Vector other) -> Vector & {
  x -= other.x;
  y -= other.y;
  return *this;
}

auto Vector::operator*=(float scalar) -> Vector & {
  x *= scalar;
  y *= scalar;
  return *this;
}

auto Vector::operator+(Vector other) const -> Vector {
  return {x + other.x, y + other.y};
}

auto Vector::operator-(Vector other) const -> Vector {
  return {x - other.x, y - other.y};
}

auto Vector::operator*(float scalar) const -> Vector {
  return {x * scalar, y * scalar};
}

auto Point::is_within(Rectangle rect) const -> bool {
  return (x >= rect.x && x <= rect.x + rect.w) &&
         (y >= rect.y && y <= rect.y + rect.h);
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

auto Point::operator-(Point p) const -> Vector { return {x - p.x, y - p.y}; }
