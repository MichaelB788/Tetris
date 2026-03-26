#pragma once

struct Point {
public:
  int x, y;

public:
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

public:
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

public:
  Point operator-() { return {x * -1, y * -1}; }
};
