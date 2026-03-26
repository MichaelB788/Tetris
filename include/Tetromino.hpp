#pragma once
#include <Point.hpp>
#include <array>
#include <cstdint>
#include <span>

class Tetromino {
public:
  enum Type : uint8_t { I = 0, O, T, S, Z, J, L };

  enum Rotation : uint8_t { R0 = 0, R90, R180, R270 };

  constexpr Tetromino(Type t = I)
      : type_(t), rotation_(R0), shape_(shapes[type_]) {}

  static Tetromino random_piece();

public:
  void shift(Point delta) {
    for (auto &tile : shape_)
      tile += delta;
  }

  void set_pos(Point pos) { shift(pos - shape_.front()); }

  void rotate_clockwise();

  void rotate_counterclockwise();

public:
  [[nodiscard]] Type type() const { return type_; }

  [[nodiscard]] auto shape() const { return std::span(shape_); }

  [[nodiscard]] Rotation rotation() const { return rotation_; }

private:
  Type type_;

  Rotation rotation_;

  std::array<Point, 4> shape_;

private:
  static constexpr std::array<std::array<Point, 4>, 7> shapes{{
      {{{0, 0}, {-1, 0}, {1, 0}, {2, 0}}},   // I
      {{{0, 0}, {1, 0}, {0, -1}, {1, -1}}},  // O
      {{{0, 0}, {-1, 0}, {1, 0}, {0, -1}}},  // T
      {{{0, 0}, {-1, 0}, {0, -1}, {1, -1}}}, // S
      {{{0, 0}, {-1, -1}, {0, -1}, {1, 0}}}, // Z
      {{{0, 0}, {-1, -1}, {-1, 0}, {1, 0}}}, // J
      {{{0, 0}, {1, -1}, {1, 0}, {-1, 0}}}   // L
  }};
};
