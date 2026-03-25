#pragma once
#include <Point.hpp>
#include <array>
#include <cstdint>
#include <span>

class Tetromino {
public:
  enum class Type : uint8_t { I = 0, O, T, S, Z, J, L };

public:
  Tetromino(Type t = Type::I);

  static Tetromino rand();

public:
  void shift(Point delta) {
    for (auto &tile : blocks_)
      tile += delta;
  }

  void set_pos(Point pos) { shift(pos - blocks_.front()); }

  void rotate_clockwise();

  void rotate_counterclockwise();

public:
  [[nodiscard]] Type type() const { return type_; }

  [[nodiscard]] auto shape() const { return std::span(blocks_); }

  [[nodiscard]] uint8_t rotation() const { return rotation_; }

private:
  Type type_;

  std::array<Point, 4> blocks_;

  uint8_t rotation_;
};
