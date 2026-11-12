#pragma once

struct Rectangle {
  float x{}, y{}, w{}, h{};
};

struct Vector {
  float x{}, y{};

  auto operator+=(Vector other) -> Vector &;
  auto operator-=(Vector other) -> Vector &;
  auto operator*=(float scalar) -> Vector &;

  [[nodiscard]] auto operator+(Vector other) const -> Vector;
  [[nodiscard]] auto operator-(Vector other) const -> Vector;
  [[nodiscard]] auto operator*(float scalar) const -> Vector;
};

struct Point {
  float x{}, y{};

  [[nodiscard]] auto is_within(Rectangle rect) const -> bool;

  auto operator+=(Vector vec) -> Point &;
  auto operator-=(Vector vec) -> Point &;

  [[nodiscard]] auto operator+(Vector vec) const -> Point;
  [[nodiscard]] auto operator-(Vector vec) const -> Point;

  [[nodiscard]] auto operator-(Point other) const -> Vector;
};
