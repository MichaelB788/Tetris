#pragma once

struct Point {
  int x, y;

  static constexpr Point up() { return {.x = 0, .y = -1}; }

  static constexpr Point down() { return {.x = 0, .y = 1}; }

  static constexpr Point left() { return {.x = -1, .y = 0}; }

  static constexpr Point right() { return {.x = 1, .y = 0}; }

  Point operator+(const Point &other) const {
    return {x + other.x, y + other.y};
  }

  Point operator-(const Point &other) const {
    return {x - other.x, y - other.y};
  }

  Point operator*(const Point &other) const {
    return {x * other.x, y * other.y};
  }

  Point operator/(const Point &other) const {
    return {x / other.x, y / other.y};
  }

  void operator+=(const Point &other) {
    x += other.x;
    y += other.y;
  }

  void operator-=(const Point &other) {
    x -= other.x;
    y -= other.y;
  }

  void operator*=(const Point &other) {
    x *= other.x;
    y *= other.y;
  }

  void operator/=(const Point &other) {
    x /= other.x;
    y /= other.y;
  }

  Point operator-() { return {x * -1, y * -1}; }
};
