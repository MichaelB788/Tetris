#pragma once

#include <type_traits>
template <typename T>
  requires std::is_arithmetic_v<T>
struct Point {
  T x, y;

  Point operator+(Point other) const { return {x + other.x, y + other.y}; }
  Point operator-(Point other) const { return {x - other.x, y - other.y}; }
  Point operator*(Point other) const { return {x * other.x, y * other.y}; }
  Point operator/(Point other) const { return {x / other.x, y / other.y}; }

  Point operator*(T val) const { return {x * val, y * val}; }
  Point operator/(T val) const { return {x / val, y / val}; }

  Point operator-() { return {x * -1, y * -1}; }

  void operator+=(Point other) {
    x += other.x;
    y += other.y;
  }
  void operator-=(Point other) {
    x -= other.x;
    y -= other.y;
  }
  void operator*=(Point other) {
    x *= other.x;
    y *= other.y;
  }
  void operator/=(Point other) {
    x /= other.x;
    y /= other.y;
  }
  void operator*=(T val) {
    x *= val;
    y *= val;
  }
  void operator/=(T val) {
    x /= val;
    y /= val;
  }
};
