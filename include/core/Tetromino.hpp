#pragma once
#include "util/Point.hpp"
#include <array>
#include <cstddef>
#include <cstdint>

class Tetromino {
public:
  static constexpr size_t NUM_TETROMINO = 7;
  static constexpr size_t NUM_ROTATION = 4;

  enum Type : uint8_t { I = 0, O, T, S, Z, J, L };
  enum Rotation : uint8_t { R0 = 0, R90, R180, R270 };

  using Shape = std::array<Point, 4>;

  constexpr Tetromino(Type t = I, Point pos = {0, 0}, Rotation r = R0)
      : type_(t), pos_(pos), rotation_(r) {}

  static Type random_type();

  static Tetromino random_piece() { return Tetromino(random_type()); }

  void shift(Point delta) { pos_ += delta; }

  void set_pos(Point pos) { pos_ = pos; }

  void rotate_cw() {
    rotation_ = static_cast<Rotation>((rotation_ + 1) % NUM_ROTATION);
  }

  void rotate_ccw() {
    rotation_ =
        static_cast<Rotation>((rotation_ + NUM_ROTATION - 1) % NUM_ROTATION);
  }

  void set_rotation(Rotation r) { rotation_ = r; }

  [[nodiscard]] Shape test_shift(Point delta) const;

  [[nodiscard]] Shape shape() const;

  [[nodiscard]] Type type() const { return type_; }

  [[nodiscard]] Point pos() const { return pos_; }

  [[nodiscard]] Rotation rotation() const { return rotation_; }

private:
  Type type_;

  Point pos_;

  Rotation rotation_;
};
