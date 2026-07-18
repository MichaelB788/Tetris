#pragma once
#include <type_traits>

template <typename T>
  requires std::is_arithmetic_v<T>
struct Point {
  T x, y;

  [[nodiscard]] auto operator+(Point other) const -> Point {
    return {x + other.x, y + other.y};
  }
  [[nodiscard]] auto operator-(Point other) const -> Point {
    return {x - other.x, y - other.y};
  }
  [[nodiscard]] auto operator*(Point other) const -> Point {
    return {x * other.x, y * other.y};
  }
  [[nodiscard]] auto operator/(Point other) const -> Point {
    return {x / other.x, y / other.y};
  }

  [[nodiscard]] auto operator*(T val) const -> Point {
    return {x * val, y * val};
  }
  [[nodiscard]] auto operator/(T val) const -> Point {
    return {x / val, y / val};
  }

  auto operator-() const -> Point { return {x * -1, y * -1}; }

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
