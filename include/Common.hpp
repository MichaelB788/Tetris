#ifndef COMMON_HPP
#define COMMON_HPP
#include <cstdint>

enum class TetrominoType : uint8_t { I, O, T, S, Z, J, L };

enum class MatrixCell : uint8_t { I, O, T, S, Z, J, L, Empty };

struct Point {
  int x, y;

  [[nodiscard]] Point rotate_clockwise(Point pivot) const {
    Point delta = *this - pivot;
    return Point((pivot.x - delta.y), (pivot.y + delta.x));
  }

  [[nodiscard]] Point rotate_counterclockwise(Point pivot) const {
    Point delta = *this - pivot;
    return Point((pivot.x + delta.y), (pivot.y - delta.x));
  }

  Point operator+(const Point &other) const {
    return Point(x + other.x, y + other.y);
  }

  Point operator-(const Point &other) const {
    return Point(x - other.x, y - other.y);
  }

  Point operator*(const Point &other) const {
    return Point(x * other.x, y * other.y);
  }

  Point operator/(const Point &other) const {
    return Point(x / other.x, y / other.y);
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

  void operator+=(int val) {
    x += val;
    y += val;
  }

  void operator-=(int val) {
    x -= val;
    y -= val;
  }

  void operator*=(int val) {
    x *= val;
    y *= val;
  }

  void operator/=(int val) {
    x /= val;
    y /= val;
  }
};

#endif
